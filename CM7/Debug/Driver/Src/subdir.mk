################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/Src/Encoder.c \
../Driver/Src/SystemClock.c \
../Driver/Src/Systick_timer.c \
../Driver/Src/gpio.c \
../Driver/Src/motor.c \
../Driver/Src/pwm.c \
../Driver/Src/uart.c 

OBJS += \
./Driver/Src/Encoder.o \
./Driver/Src/SystemClock.o \
./Driver/Src/Systick_timer.o \
./Driver/Src/gpio.o \
./Driver/Src/motor.o \
./Driver/Src/pwm.o \
./Driver/Src/uart.o 

C_DEPS += \
./Driver/Src/Encoder.d \
./Driver/Src/SystemClock.d \
./Driver/Src/Systick_timer.d \
./Driver/Src/gpio.d \
./Driver/Src/motor.d \
./Driver/Src/pwm.d \
./Driver/Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/Src/%.o Driver/Src/%.su Driver/Src/%.cyclo: ../Driver/Src/%.c Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DSTM32H755ZITx -DSTM32 -DSTM32H7DUAL -DSTM32H7 -DNUCLEO_H755ZI_Q -DCORE_CM7 -DSTM32H755xx -c -I../Inc -I"C:/Users/Admin/Documents/DSP_AI_STM32/CMSIS/Device/ST/STM32H7xx/Include" -I"C:/Users/Admin/Documents/DSP_AI_STM32/CMSIS/Include" -I"C:/Users/Admin/Documents/DSP_AI_STM32/Motor_control/CM7/Driver/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Driver-2f-Src

clean-Driver-2f-Src:
	-$(RM) ./Driver/Src/Encoder.cyclo ./Driver/Src/Encoder.d ./Driver/Src/Encoder.o ./Driver/Src/Encoder.su ./Driver/Src/SystemClock.cyclo ./Driver/Src/SystemClock.d ./Driver/Src/SystemClock.o ./Driver/Src/SystemClock.su ./Driver/Src/Systick_timer.cyclo ./Driver/Src/Systick_timer.d ./Driver/Src/Systick_timer.o ./Driver/Src/Systick_timer.su ./Driver/Src/gpio.cyclo ./Driver/Src/gpio.d ./Driver/Src/gpio.o ./Driver/Src/gpio.su ./Driver/Src/motor.cyclo ./Driver/Src/motor.d ./Driver/Src/motor.o ./Driver/Src/motor.su ./Driver/Src/pwm.cyclo ./Driver/Src/pwm.d ./Driver/Src/pwm.o ./Driver/Src/pwm.su ./Driver/Src/uart.cyclo ./Driver/Src/uart.d ./Driver/Src/uart.o ./Driver/Src/uart.su

.PHONY: clean-Driver-2f-Src

