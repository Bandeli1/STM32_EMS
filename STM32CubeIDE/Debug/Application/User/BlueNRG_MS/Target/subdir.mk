################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/elias/Dokumente/ETH/Sem5/PnS/Sensor\ and\ IoT/My\ Project/EM_System/BlueNRG_MS/Target/hci_tl_interface.c 

OBJS += \
./Application/User/BlueNRG_MS/Target/hci_tl_interface.o 

C_DEPS += \
./Application/User/BlueNRG_MS/Target/hci_tl_interface.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/BlueNRG_MS/Target/hci_tl_interface.o: /home/elias/Dokumente/ETH/Sem5/PnS/Sensor\ and\ IoT/My\ Project/EM_System/BlueNRG_MS/Target/hci_tl_interface.c Application/User/BlueNRG_MS/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L475xx -c -I../../Core/Inc -I"/home/elias/Dokumente/ETH/Sem5/PnS/Sensor and IoT/My Project/EM_System/Drivers/BSP/B-L475E-IOT01" -I"/home/elias/Dokumente/ETH/Sem5/PnS/Sensor and IoT/My Project/EM_System/Drivers/BSP/Components" -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../BlueNRG_MS/App -I../../BlueNRG_MS/Target -I../../Middlewares/ST/BlueNRG-MS/utils -I../../Middlewares/ST/BlueNRG-MS/includes -I../../Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Application/User/BlueNRG_MS/Target/hci_tl_interface.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-BlueNRG_MS-2f-Target

clean-Application-2f-User-2f-BlueNRG_MS-2f-Target:
	-$(RM) ./Application/User/BlueNRG_MS/Target/hci_tl_interface.cyclo ./Application/User/BlueNRG_MS/Target/hci_tl_interface.d ./Application/User/BlueNRG_MS/Target/hci_tl_interface.o ./Application/User/BlueNRG_MS/Target/hci_tl_interface.su

.PHONY: clean-Application-2f-User-2f-BlueNRG_MS-2f-Target

