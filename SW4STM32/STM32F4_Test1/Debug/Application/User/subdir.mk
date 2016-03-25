################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/chip_select_demux.c \
D:/RoboCup/GitHub/RobotMCU/Src/freertos.c \
D:/RoboCup/GitHub/RobotMCU/Src/main.c \
../Application/User/quad_driver.c \
../Application/User/spi_wrapper.c \
D:/RoboCup/GitHub/RobotMCU/Src/stm32f4xx_hal_msp.c \
D:/RoboCup/GitHub/RobotMCU/Src/stm32f4xx_hal_timebase_TIM.c \
D:/RoboCup/GitHub/RobotMCU/Src/stm32f4xx_it.c \
D:/RoboCup/GitHub/RobotMCU/Src/usb_device.c \
D:/RoboCup/GitHub/RobotMCU/Src/usbd_cdc_if.c \
D:/RoboCup/GitHub/RobotMCU/Src/usbd_conf.c \
D:/RoboCup/GitHub/RobotMCU/Src/usbd_desc.c 

OBJS += \
./Application/User/chip_select_demux.o \
./Application/User/freertos.o \
./Application/User/main.o \
./Application/User/quad_driver.o \
./Application/User/spi_wrapper.o \
./Application/User/stm32f4xx_hal_msp.o \
./Application/User/stm32f4xx_hal_timebase_TIM.o \
./Application/User/stm32f4xx_it.o \
./Application/User/usb_device.o \
./Application/User/usbd_cdc_if.o \
./Application/User/usbd_conf.o \
./Application/User/usbd_desc.o 

C_DEPS += \
./Application/User/chip_select_demux.d \
./Application/User/freertos.d \
./Application/User/main.d \
./Application/User/quad_driver.d \
./Application/User/spi_wrapper.d \
./Application/User/stm32f4xx_hal_msp.d \
./Application/User/stm32f4xx_hal_timebase_TIM.d \
./Application/User/stm32f4xx_it.d \
./Application/User/usb_device.d \
./Application/User/usbd_cdc_if.d \
./Application/User/usbd_conf.d \
./Application/User/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/%.o: ../Application/User/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Include" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/freertos.o: D:/RoboCup/GitHub/RobotMCU/Src/freertos.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Include" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/main.o: D:/RoboCup/GitHub/RobotMCU/Src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Include" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_hal_msp.o: D:/RoboCup/GitHub/RobotMCU/Src/stm32f4xx_hal_msp.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Include" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_hal_timebase_TIM.o: D:/RoboCup/GitHub/RobotMCU/Src/stm32f4xx_hal_timebase_TIM.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Include" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_it.o: D:/RoboCup/GitHub/RobotMCU/Src/stm32f4xx_it.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Include" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usb_device.o: D:/RoboCup/GitHub/RobotMCU/Src/usb_device.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Include" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usbd_cdc_if.o: D:/RoboCup/GitHub/RobotMCU/Src/usbd_cdc_if.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Include" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usbd_conf.o: D:/RoboCup/GitHub/RobotMCU/Src/usbd_conf.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Include" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usbd_desc.o: D:/RoboCup/GitHub/RobotMCU/Src/usbd_desc.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"D:/RoboCup/GitHub/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Include" -I"D:/RoboCup/GitHub/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/RoboCup/GitHub/RobotMCU/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"D:/RoboCup/GitHub/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


