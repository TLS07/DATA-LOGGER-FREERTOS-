################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/event_groups.c \
../Src/function.c \
../Src/heap_4.c \
../Src/init.c \
../Src/list.c \
../Src/main.c \
../Src/port.c \
../Src/program_tasks.c \
../Src/queue.c \
../Src/stream_buffer.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/tasks.c \
../Src/timers.c 

OBJS += \
./Src/event_groups.o \
./Src/function.o \
./Src/heap_4.o \
./Src/init.o \
./Src/list.o \
./Src/main.o \
./Src/port.o \
./Src/program_tasks.o \
./Src/queue.o \
./Src/stream_buffer.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/tasks.o \
./Src/timers.o 

C_DEPS += \
./Src/event_groups.d \
./Src/function.d \
./Src/heap_4.d \
./Src/init.d \
./Src/list.d \
./Src/main.d \
./Src/port.d \
./Src/program_tasks.d \
./Src/queue.d \
./Src/stream_buffer.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/tasks.d \
./Src/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"C:/Users/Admin/Desktop/ip/stm/FREE_12_2/Middlewares/FreeRTOS/portable/GCC/ARM_CM3" -I"C:/Users/Admin/Desktop/ip/stm/FREE_12_2/Middlewares/FreeRTOS/include" -I"C:/Users/Admin/Desktop/ip/stm/FREE_12_2/Middlewares/FreeRTOS/include" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/event_groups.cyclo ./Src/event_groups.d ./Src/event_groups.o ./Src/event_groups.su ./Src/function.cyclo ./Src/function.d ./Src/function.o ./Src/function.su ./Src/heap_4.cyclo ./Src/heap_4.d ./Src/heap_4.o ./Src/heap_4.su ./Src/init.cyclo ./Src/init.d ./Src/init.o ./Src/init.su ./Src/list.cyclo ./Src/list.d ./Src/list.o ./Src/list.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/port.cyclo ./Src/port.d ./Src/port.o ./Src/port.su ./Src/program_tasks.cyclo ./Src/program_tasks.d ./Src/program_tasks.o ./Src/program_tasks.su ./Src/queue.cyclo ./Src/queue.d ./Src/queue.o ./Src/queue.su ./Src/stream_buffer.cyclo ./Src/stream_buffer.d ./Src/stream_buffer.o ./Src/stream_buffer.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/tasks.cyclo ./Src/tasks.d ./Src/tasks.o ./Src/tasks.su ./Src/timers.cyclo ./Src/timers.d ./Src/timers.o ./Src/timers.su

.PHONY: clean-Src

