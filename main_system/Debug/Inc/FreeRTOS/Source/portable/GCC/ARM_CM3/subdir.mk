################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/FreeRTOS/Source/portable/GCC/ARM_CM3/port.c 

OBJS += \
./Inc/FreeRTOS/Source/portable/GCC/ARM_CM3/port.o 

C_DEPS += \
./Inc/FreeRTOS/Source/portable/GCC/ARM_CM3/port.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/FreeRTOS/Source/portable/GCC/ARM_CM3/%.o Inc/FreeRTOS/Source/portable/GCC/ARM_CM3/%.su Inc/FreeRTOS/Source/portable/GCC/ARM_CM3/%.cyclo: ../Inc/FreeRTOS/Source/portable/GCC/ARM_CM3/%.c Inc/FreeRTOS/Source/portable/GCC/ARM_CM3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103RBTx -DSTM32 -DSTM32F1 -c -I../Inc -I"/home/kiyun/paper/projects/RC_car/main_system/Src" -I"/home/kiyun/paper/projects/RC_car/main_system/Inc/FreeRTOS/Source/CMSIS_RTOS" -I"/home/kiyun/paper/projects/RC_car/main_system/Inc/FreeRTOS/Source/include" -I"/home/kiyun/paper/projects/RC_car/main_system/Inc/FreeRTOS/Source/portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Inc-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM3

clean-Inc-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM3:
	-$(RM) ./Inc/FreeRTOS/Source/portable/GCC/ARM_CM3/port.cyclo ./Inc/FreeRTOS/Source/portable/GCC/ARM_CM3/port.d ./Inc/FreeRTOS/Source/portable/GCC/ARM_CM3/port.o ./Inc/FreeRTOS/Source/portable/GCC/ARM_CM3/port.su

.PHONY: clean-Inc-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM3

