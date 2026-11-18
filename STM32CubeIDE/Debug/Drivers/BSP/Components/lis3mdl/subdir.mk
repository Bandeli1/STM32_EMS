################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/elias/Dokumente/ETH/Sem5/PnS/Sensor\ and\ IoT/My\ Project/EM_System/Drivers/BSP/Components/lis3mdl/lis3mdl.c 

OBJS += \
./Drivers/BSP/Components/lis3mdl/lis3mdl.o 

C_DEPS += \
./Drivers/BSP/Components/lis3mdl/lis3mdl.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/lis3mdl/lis3mdl.o: /home/elias/Dokumente/ETH/Sem5/PnS/Sensor\ and\ IoT/My\ Project/EM_System/Drivers/BSP/Components/lis3mdl/lis3mdl.c Drivers/BSP/Components/lis3mdl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../../Core/Inc -I"/home/elias/Dokumente/ETH/Sem5/PnS/Sensor and IoT/My Project/EM_System/Drivers/BSP/B-L475E-IOT01" -I"/home/elias/Dokumente/ETH/Sem5/PnS/Sensor and IoT/My Project/EM_System/Drivers/BSP/Components" -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../BlueNRG_MS/App -I../../BlueNRG_MS/Target -I../../Middlewares/ST/BlueNRG-MS/utils -I../../Middlewares/ST/BlueNRG-MS/includes -I../../Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-lis3mdl

clean-Drivers-2f-BSP-2f-Components-2f-lis3mdl:
	-$(RM) ./Drivers/BSP/Components/lis3mdl/lis3mdl.cyclo ./Drivers/BSP/Components/lis3mdl/lis3mdl.d ./Drivers/BSP/Components/lis3mdl/lis3mdl.o ./Drivers/BSP/Components/lis3mdl/lis3mdl.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-lis3mdl

