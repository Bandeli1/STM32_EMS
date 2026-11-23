#ifndef LIGHT_BAR_H
#define LIGHT_BAR_H

#include "main.h"
#include <stdint.h>

/* ---- Light measurement (VL53L0X ambient rate) ---- */
int   Light_Init(void);              /* returns 0 on success            */
int   Light_Read(float *ambient);    /* ambient rate in MCPS, 0 = ok    */

/* ---- LED stick (8x SK6812 RGBW on TIM1 CH1 / PA8, DMA) ---- */
void  Led_Init(TIM_HandleTypeDef *htim, uint32_t channel);
void  Led_ShowBar(float level);      /* level 0.0 .. 1.0                */
void  Led_Clear(void);

/* ---- Helper: raw ambient -> 0..1 (log scale, smoothed) ---- */
float Light_ToLevel(float ambient);

#endif
