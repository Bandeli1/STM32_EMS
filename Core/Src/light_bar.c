#include "light_bar.h"
/* 1 = fake light value (ramps up and down) -> test LED bar without the sensor driver
 * 0 = real VL53L0X ambient value (needs the ST VL53L0X API in the project) */
#define LIGHT_SIMULATE   1

#if !LIGHT_SIMULATE
#include "vl53l0x_api.h"      /* ST VL53L0X API (BSP component or X-CUBE-TOF1) */
#endif
#include <math.h>
#include <string.h>

/* ======================================================================
 * 1) LIGHT: VL53L0X ambient rate
 *    Needs: XSHUT = PC6 as GPIO output, I2C2 initialised by CubeMX,
 *    and the VL53L0X platform layer (vl53l0x_platform.c) using hi2c2.
 * ====================================================================== */

#define VL53_XSHUT_PORT   GPIOC
#define VL53_XSHUT_PIN    GPIO_PIN_6

/* Calibrate these by measuring: hand over sensor = MIN, flashlight = MAX */
#define LIGHT_MIN         0.5f    /* MCPS, darkness  */
#define LIGHT_MAX         30.0f   /* MCPS, bright    */

#if !LIGHT_SIMULATE
static VL53L0X_Dev_t vl53;

int Light_Init(void)
{
    uint32_t refSpadCount;
    uint8_t  isApertureSpads, vhvSettings, phaseCal;

    /* wake sensor up */
    HAL_GPIO_WritePin(VL53_XSHUT_PORT, VL53_XSHUT_PIN, GPIO_PIN_SET);
    HAL_Delay(10);

    vl53.I2cDevAddr = 0x52;   /* 8-bit address; field names can differ per platform layer */

    if (VL53L0X_DataInit(&vl53)   != VL53L0X_ERROR_NONE) return -1;
    if (VL53L0X_StaticInit(&vl53) != VL53L0X_ERROR_NONE) return -2;
    if (VL53L0X_PerformRefSpadManagement(&vl53, &refSpadCount, &isApertureSpads) != VL53L0X_ERROR_NONE) return -3;
    if (VL53L0X_PerformRefCalibration(&vl53, &vhvSettings, &phaseCal)            != VL53L0X_ERROR_NONE) return -4;
    if (VL53L0X_SetDeviceMode(&vl53, VL53L0X_DEVICEMODE_SINGLE_RANGING)          != VL53L0X_ERROR_NONE) return -5;
    return 0;
}

int Light_Read(float *ambient)
{
    VL53L0X_RangingMeasurementData_t m;

    if (VL53L0X_PerformSingleRangingMeasurement(&vl53, &m) != VL53L0X_ERROR_NONE)
        return -1;

    /* FixPoint16.16 -> float, unit: mega counts per second */
    *ambient = (float)m.AmbientRateRtnMegaCps / 65536.0f;
    return 0;
}

#else  /* LIGHT_SIMULATE: fake value, rises and falls between LIGHT_MIN and LIGHT_MAX */

int Light_Init(void) { return 0; }

int Light_Read(float *ambient)
{
    static float x = LIGHT_MIN;
    static int   up = 1;

    x *= up ? 1.15f : 0.87f;
    if (x >= LIGHT_MAX) { x = LIGHT_MAX; up = 0; }
    if (x <= LIGHT_MIN) { x = LIGHT_MIN; up = 1; }

    *ambient = x;
    return 0;
}

#endif

float Light_ToLevel(float ambient)
{
    static float filtered = 0.0f;

    if (ambient < LIGHT_MIN) ambient = LIGHT_MIN;
    if (ambient > LIGHT_MAX) ambient = LIGHT_MAX;

    /* log scale: dim light still visible, bright light does not saturate instantly */
    float lvl = (logf(ambient) - logf(LIGHT_MIN)) / (logf(LIGHT_MAX) - logf(LIGHT_MIN));

    /* smoothing, so the bar does not flicker */
    filtered += 0.3f * (lvl - filtered);
    return filtered;
}

/* ======================================================================
 * 2) LED STICK: 8x SK6812 RGBW (Adafruit NeoPixel Stick RGBW)
 *    NOT PA8: that pin is already the BLE reset line in your project.
 *    Use a free pin with a timer channel, e.g. PA15 = TIM2_CH1 (check
 *    that it is free on your board / Arduino header).
 *    CubeMX setup (80 MHz system clock):
 *      TIM2: Channel1 = PWM Generation CH1, Prescaler = 0, Counter Period (ARR) = 99
 *            (-> 800 kHz = 1.25 us per bit)
 *      DMA Settings: add TIM2_CH1, direction Memory to Peripheral,
 *            Data Width: Half Word / Half Word, Increment memory = on, Mode = Normal
 * ====================================================================== */

#define LED_COUNT        8
#define BITS_PER_LED     32            /* G, R, B, W = 4 bytes */
#define RESET_SLOTS      80            /* >80 us low = latch   */
#define LED_BUF_LEN      (LED_COUNT * BITS_PER_LED + RESET_SLOTS)

/* Timer ticks for a "0" and a "1" bit. Calculated in Led_Init() from the real
 * timer clock, so it works at 4 MHz (your current clock), 80 MHz, or anything else. */
static uint16_t t0h, t1h;

#define MAX_BRIGHTNESS   60            /* 0..255, keep low: 8 LEDs at full white draw a lot */

static TIM_HandleTypeDef *led_tim;
static uint32_t           led_ch;
static uint16_t           led_buf[LED_BUF_LEN];
static volatile uint8_t   led_busy = 0;

void Led_Init(TIM_HandleTypeDef *htim, uint32_t channel)
{
    led_tim = htim;
    led_ch  = channel;

    /* timer clock = PCLK1, or 2x PCLK1 if the APB1 prescaler is not 1 */
    uint32_t tclk = HAL_RCC_GetPCLK1Freq();
    if ((RCC->CFGR & RCC_CFGR_PPRE1) != RCC_CFGR_PPRE1_DIV1) tclk *= 2;

    /* 800 kHz bit rate (1.25 us), "0" = ~0.32 us high, "1" = ~0.62 us high */
    __HAL_TIM_SET_AUTORELOAD(htim, tclk / 800000UL - 1);
    t0h = (uint16_t)(((uint64_t)tclk * 32U + 50000000U) / 100000000U);
    t1h = (uint16_t)(((uint64_t)tclk * 62U + 50000000U) / 100000000U);
    if (t0h < 1) t0h = 1;

    Led_Clear();
}

static void led_set(uint8_t idx, uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{
    uint32_t grbw = ((uint32_t)g << 24) | ((uint32_t)r << 16) | ((uint32_t)b << 8) | w;
    uint16_t *p = &led_buf[idx * BITS_PER_LED];

    for (int i = 0; i < 32; i++)
        p[i] = (grbw & (1UL << (31 - i))) ? t1h : t0h;
}

static void led_send(void)
{
    uint32_t t_start = HAL_GetTick();
    while (led_busy) {                 /* wait for previous frame (takes ~0.5 ms) */
        if (HAL_GetTick() - t_start > 10) {   /* callback never came: do not freeze the program */
            HAL_TIM_PWM_Stop_DMA(led_tim, led_ch);
            led_busy = 0;
            break;
        }
    }
    led_busy = 1;
    if (HAL_TIM_PWM_Start_DMA(led_tim, led_ch, (uint32_t *)led_buf, LED_BUF_LEN) != HAL_OK)
        led_busy = 0;
}

/* called by HAL when the DMA transfer is done */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == led_tim) {
        HAL_TIM_PWM_Stop_DMA(htim, led_ch);
        led_busy = 0;
    }
}

void Led_Clear(void)
{
    memset(led_buf, 0, sizeof(led_buf));
    for (int i = 0; i < LED_COUNT; i++) led_set(i, 0, 0, 0, 0);
    led_send();
}

/* level 0.0 .. 1.0 -> bar of 8 LEDs, last LED partly lit */
void Led_ShowBar(float level)
{
    if (level < 0.0f) level = 0.0f;
    if (level > 1.0f) level = 1.0f;

    float pos = level * LED_COUNT;           /* 0 .. 8 */

    memset(led_buf, 0, sizeof(led_buf));
    for (int i = 0; i < LED_COUNT; i++) {
        float f = pos - (float)i;            /* how much of this LED is "filled" */
        if (f > 1.0f) f = 1.0f;
        if (f < 0.0f) f = 0.0f;

        uint8_t bright = (uint8_t)(f * MAX_BRIGHTNESS);
        /* warm white: mostly W channel plus a little red */
        led_set(i, bright / 4, 0, 0, bright);
    }
    led_send();
}
