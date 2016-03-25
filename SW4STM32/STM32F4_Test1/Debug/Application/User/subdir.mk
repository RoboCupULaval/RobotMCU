################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/RoboCup/STM32F4_Test1/Src/freertos.c \
D:/RoboCup/STM32F4_Test1/Src/main.c \
D:/RoboCup/STM32F4_Test1/Src/stm32f4xx_hal_msp.c \
D:/RoboCup/STM32F4_Test1/Src/stm32f4xx_hal_timebase_TIM.c \
D:/RoboCup/STM32F4_Test1/Src/stm32f4xx_it.c 

OBJS += \
./Application/User/freertos.o \
./Application/User/main.o \
./Application/User/stm32f4xx_hal_msp.o \
./Application/User/stm32f4xx_hal_timebase_TIM.o \
./Application/User/stm32f4xx_it.o 

C_DEPS += \
./Application/User/freertos.d \
./Application/User/main.d \
./Application/User/stm32f4xx_hal_msp.d \
./Application/User/stm32f4xx_hal_timebase_TIM.d \
./Application/User/stm32f4xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/freertos.o: D:/RoboCup/STM32F4_Test1/Src/freertos.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/STM32F4_Test1/Inc" -I"D:/RoboCup/STM32F4_Test1/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/STM32F4_Test1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/STM32F4_Test1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/STM32F4_Test1/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/STM32F4_Test1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/STM32F4_Test1/Drivers/CMSIS/Include" -I"D:/RoboCup/STM32F4_Test1/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/RoboCup/STM32F4_Test1/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/main.o: D:/RoboCup/STM32F4_Test1/Src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/STM32F4_Test1/Inc" -I"D:/RoboCup/STM32F4_Test1/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/STM32F4_Test1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/STM32F4_Test1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/STM32F4_Test1/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/STM32F4_Test1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/STM32F4_Test1/Drivers/CMSIS/Include" -I"D:/RoboCup/STM32F4_Test1/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/RoboCup/STM32F4_Test1/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_hal_msp.o: D:/RoboCup/STM32F4_Test1/Src/stm32f4xx_hal_msp.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/STM32F4_Test1/Inc" -I"D:/RoboCup/STM32F4_Test1/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/STM32F4_Test1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/STM32F4_Test1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/STM32F4_Test1/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/STM32F4_Test1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/STM32F4_Test1/Drivers/CMSIS/Include" -I"D:/RoboCup/STM32F4_Test1/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/RoboCup/STM32F4_Test1/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_hal_timebase_TIM.o: D:/RoboCup/STM32F4_Test1/Src/stm32f4xx_hal_timebase_TIM.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/STM32F4_Test1/Inc" -I"D:/RoboCup/STM32F4_Test1/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/STM32F4_Test1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/STM32F4_Test1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/STM32F4_Test1/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/STM32F4_Test1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/STM32F4_Test1/Drivers/CMSIS/Include" -I"D:/RoboCup/STM32F4_Test1/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/RoboCup/STM32F4_Test1/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_it.o: D:/RoboCup/STM32F4_Test1/Src/stm32f4xx_it.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/STM32F4_Test1/Inc" -I"D:/RoboCup/STM32F4_Test1/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/STM32F4_Test1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/STM32F4_Test1/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/STM32F4_Test1/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/STM32F4_Test1/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/STM32F4_Test1/Drivers/CMSIS/Include" -I"D:/RoboCup/STM32F4_Test1/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/RoboCup/STM32F4_Test1/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


