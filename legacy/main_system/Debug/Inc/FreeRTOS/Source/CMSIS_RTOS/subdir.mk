################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c 

OBJS += \
./Inc/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.o 

C_DEPS += \
./Inc/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/FreeRTOS/Source/CMSIS_RTOS/%.o Inc/FreeRTOS/Source/CMSIS_RTOS/%.su Inc/FreeRTOS/Source/CMSIS_RTOS/%.cyclo: ../Inc/FreeRTOS/Source/CMSIS_RTOS/%.c Inc/FreeRTOS/Source/CMSIS_RTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103RBTx -DSTM32 -DSTM32F1 -c -I../Inc -I"/home/kiyun/paper/projects/RC_car/main_system/Src" -I"/home/kiyun/paper/projects/RC_car/main_system/Inc/FreeRTOS/Source/CMSIS_RTOS" -I"/home/kiyun/paper/projects/RC_car/main_system/Inc/FreeRTOS/Source/include" -I"/home/kiyun/paper/projects/RC_car/main_system/Inc/FreeRTOS/Source/portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Inc-2f-FreeRTOS-2f-Source-2f-CMSIS_RTOS

clean-Inc-2f-FreeRTOS-2f-Source-2f-CMSIS_RTOS:
	-$(RM) ./Inc/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.cyclo ./Inc/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.d ./Inc/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.o ./Inc/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.su

.PHONY: clean-Inc-2f-FreeRTOS-2f-Source-2f-CMSIS_RTOS

