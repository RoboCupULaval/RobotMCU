################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c \
D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c \
D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/list.c \
D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c \
D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/queue.c \
D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/timers.c 

OBJS += \
./Middlewares/FreeRTOS/cmsis_os.o \
./Middlewares/FreeRTOS/croutine.o \
./Middlewares/FreeRTOS/event_groups.o \
./Middlewares/FreeRTOS/heap_4.o \
./Middlewares/FreeRTOS/list.o \
./Middlewares/FreeRTOS/port.o \
./Middlewares/FreeRTOS/queue.o \
./Middlewares/FreeRTOS/tasks.o \
./Middlewares/FreeRTOS/timers.o 

C_DEPS += \
./Middlewares/FreeRTOS/cmsis_os.d \
./Middlewares/FreeRTOS/croutine.d \
./Middlewares/FreeRTOS/event_groups.d \
./Middlewares/FreeRTOS/heap_4.d \
./Middlewares/FreeRTOS/list.d \
./Middlewares/FreeRTOS/port.d \
./Middlewares/FreeRTOS/queue.d \
./Middlewares/FreeRTOS/tasks.d \
./Middlewares/FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FreeRTOS/cmsis_os.o: D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Include" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/croutine.o: D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/croutine.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Include" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/event_groups.o: D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Include" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/heap_4.o: D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Include" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/list.o: D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/list.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Include" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/port.o: D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Include" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/queue.o: D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/queue.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Include" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/tasks.o: D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/tasks.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Include" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/timers.o: D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/timers.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Include" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


