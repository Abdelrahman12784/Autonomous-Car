################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/TIMER/TIMER_config.c \
../MCAL/TIMER/TIMER_prog.c 

OBJS += \
./MCAL/TIMER/TIMER_config.o \
./MCAL/TIMER/TIMER_prog.o 

C_DEPS += \
./MCAL/TIMER/TIMER_config.d \
./MCAL/TIMER/TIMER_prog.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/TIMER/%.o: ../MCAL/TIMER/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


