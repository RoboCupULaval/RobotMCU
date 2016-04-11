################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c \
/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c \
/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/list.c \
/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c \
/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/queue.c \
/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/timers.c 

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
Middlewares/FreeRTOS/cmsis_os.o: /Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/croutine.o: /Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/croutine.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/event_groups.o: /Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/heap_4.o: /Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/list.o: /Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/list.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/port.o: /Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/queue.o: /Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/queue.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/tasks.o: /Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/tasks.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/FreeRTOS/timers.o: /Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/timers.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


