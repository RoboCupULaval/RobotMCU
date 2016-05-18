################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32f4xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32f4xx.o: D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Include" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


