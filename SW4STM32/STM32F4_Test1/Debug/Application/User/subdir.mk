################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/chip_select_demux.c \
/Users/Gagnon/Documents/Robocup/RobotMCU/Src/freertos.c \
/Users/Gagnon/Documents/Robocup/RobotMCU/Src/main.c \
../Application/User/quad_driver.c \
../Application/User/spi_wrapper.c \
/Users/Gagnon/Documents/Robocup/RobotMCU/Src/stm32f4xx_hal_msp.c \
/Users/Gagnon/Documents/Robocup/RobotMCU/Src/stm32f4xx_hal_timebase_TIM.c \
/Users/Gagnon/Documents/Robocup/RobotMCU/Src/stm32f4xx_it.c \
/Users/Gagnon/Documents/Robocup/RobotMCU/Src/usb_device.c \
/Users/Gagnon/Documents/Robocup/RobotMCU/Src/usbd_cdc_if.c \
/Users/Gagnon/Documents/Robocup/RobotMCU/Src/usbd_conf.c \
/Users/Gagnon/Documents/Robocup/RobotMCU/Src/usbd_desc.c 

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
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/freertos.o: /Users/Gagnon/Documents/Robocup/RobotMCU/Src/freertos.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/main.o: /Users/Gagnon/Documents/Robocup/RobotMCU/Src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_hal_msp.o: /Users/Gagnon/Documents/Robocup/RobotMCU/Src/stm32f4xx_hal_msp.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_hal_timebase_TIM.o: /Users/Gagnon/Documents/Robocup/RobotMCU/Src/stm32f4xx_hal_timebase_TIM.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_it.o: /Users/Gagnon/Documents/Robocup/RobotMCU/Src/stm32f4xx_it.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usb_device.o: /Users/Gagnon/Documents/Robocup/RobotMCU/Src/usb_device.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usbd_cdc_if.o: /Users/Gagnon/Documents/Robocup/RobotMCU/Src/usbd_cdc_if.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usbd_conf.o: /Users/Gagnon/Documents/Robocup/RobotMCU/Src/usbd_conf.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usbd_desc.o: /Users/Gagnon/Documents/Robocup/RobotMCU/Src/usbd_desc.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/SW4STM32/STM32F4_Test1/Application/User" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Include" -I"/Users/Gagnon/Documents/Robocup/RobotMCU/Drivers/CMSIS/Device/ST/STM32F4xx/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


