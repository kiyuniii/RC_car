################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/FreeRTOS/Source/croutine.c \
../Inc/FreeRTOS/Source/event_groups.c \
../Inc/FreeRTOS/Source/list.c \
../Inc/FreeRTOS/Source/queue.c \
../Inc/FreeRTOS/Source/stream_buffer.c \
../Inc/FreeRTOS/Source/tasks.c \
../Inc/FreeRTOS/Source/timers.c 

OBJS += \
./Inc/FreeRTOS/Source/croutine.o \
./Inc/FreeRTOS/Source/event_groups.o \
./Inc/FreeRTOS/Source/list.o \
./Inc/FreeRTOS/Source/queue.o \
./Inc/FreeRTOS/Source/stream_buffer.o \
./Inc/FreeRTOS/Source/tasks.o \
./Inc/FreeRTOS/Source/timers.o 

C_DEPS += \
./Inc/FreeRTOS/Source/croutine.d \
./Inc/FreeRTOS/Source/event_groups.d \
./Inc/FreeRTOS/Source/list.d \
./Inc/FreeRTOS/Source/queue.d \
./Inc/FreeRTOS/Source/stream_buffer.d \
./Inc/FreeRTOS/Source/tasks.d \
./Inc/FreeRTOS/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/FreeRTOS/Source/%.o Inc/FreeRTOS/Source/%.su Inc/FreeRTOS/Source/%.cyclo: ../Inc/FreeRTOS/Source/%.c Inc/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103RBTx -DSTM32 -DSTM32F1 -c -I../Inc -I"/home/kiyun/paper/projects/RC_car/main_system/Src" -I"/home/kiyun/paper/projects/RC_car/main_system/Inc/FreeRTOS/Source/CMSIS_RTOS" -I"/home/kiyun/paper/projects/RC_car/main_system/Inc/FreeRTOS/Source/include" -I"/home/kiyun/paper/projects/RC_car/main_system/Inc/FreeRTOS/Source/portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Inc-2f-FreeRTOS-2f-Source

clean-Inc-2f-FreeRTOS-2f-Source:
	-$(RM) ./Inc/FreeRTOS/Source/croutine.cyclo ./Inc/FreeRTOS/Source/croutine.d ./Inc/FreeRTOS/Source/croutine.o ./Inc/FreeRTOS/Source/croutine.su ./Inc/FreeRTOS/Source/event_groups.cyclo ./Inc/FreeRTOS/Source/event_groups.d ./Inc/FreeRTOS/Source/event_groups.o ./Inc/FreeRTOS/Source/event_groups.su ./Inc/FreeRTOS/Source/list.cyclo ./Inc/FreeRTOS/Source/list.d ./Inc/FreeRTOS/Source/list.o ./Inc/FreeRTOS/Source/list.su ./Inc/FreeRTOS/Source/queue.cyclo ./Inc/FreeRTOS/Source/queue.d ./Inc/FreeRTOS/Source/queue.o ./Inc/FreeRTOS/Source/queue.su ./Inc/FreeRTOS/Source/stream_buffer.cyclo ./Inc/FreeRTOS/Source/stream_buffer.d ./Inc/FreeRTOS/Source/stream_buffer.o ./Inc/FreeRTOS/Source/stream_buffer.su ./Inc/FreeRTOS/Source/tasks.cyclo ./Inc/FreeRTOS/Source/tasks.d ./Inc/FreeRTOS/Source/tasks.o ./Inc/FreeRTOS/Source/tasks.su ./Inc/FreeRTOS/Source/timers.cyclo ./Inc/FreeRTOS/Source/timers.d ./Inc/FreeRTOS/Source/timers.o ./Inc/FreeRTOS/Source/timers.su

.PHONY: clean-Inc-2f-FreeRTOS-2f-Source

