################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/elias/Dokumente/ETH/Sem5/PnS/Sensor\ and\ IoT/My\ Project/EM_System/Middlewares/ST/BlueNRG-MS/utils/ble_list.c 

OBJS += \
./Middlewares/BlueNRG-MS/Wireless/BlueNRG-MS/Utils/ble_list.o 

C_DEPS += \
./Middlewares/BlueNRG-MS/Wireless/BlueNRG-MS/Utils/ble_list.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/BlueNRG-MS/Wireless/BlueNRG-MS/Utils/ble_list.o: /home/elias/Dokumente/ETH/Sem5/PnS/Sensor\ and\ IoT/My\ Project/EM_System/Middlewares/ST/BlueNRG-MS/utils/ble_list.c Middlewares/BlueNRG-MS/Wireless/BlueNRG-MS/Utils/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../../Core/Inc -I"/home/elias/Dokumente/ETH/Sem5/PnS/Sensor and IoT/My Project/EM_System/Drivers/BSP/B-L475E-IOT01" -I"/home/elias/Dokumente/ETH/Sem5/PnS/Sensor and IoT/My Project/EM_System/Drivers/BSP/Components" -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../BlueNRG_MS/App -I../../BlueNRG_MS/Target -I../../Middlewares/ST/BlueNRG-MS/utils -I../../Middlewares/ST/BlueNRG-MS/includes -I../../Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Middlewares/BlueNRG-MS/Wireless/BlueNRG-MS/Utils/ble_list.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-BlueNRG-2d-MS-2f-Wireless-2f-BlueNRG-2d-MS-2f-Utils

clean-Middlewares-2f-BlueNRG-2d-MS-2f-Wireless-2f-BlueNRG-2d-MS-2f-Utils:
	-$(RM) ./Middlewares/BlueNRG-MS/Wireless/BlueNRG-MS/Utils/ble_list.cyclo ./Middlewares/BlueNRG-MS/Wireless/BlueNRG-MS/Utils/ble_list.d ./Middlewares/BlueNRG-MS/Wireless/BlueNRG-MS/Utils/ble_list.o ./Middlewares/BlueNRG-MS/Wireless/BlueNRG-MS/Utils/ble_list.su

.PHONY: clean-Middlewares-2f-BlueNRG-2d-MS-2f-Wireless-2f-BlueNRG-2d-MS-2f-Utils

