################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../gpio.c \
../lcd.c \
../motor.c \
../temp.c \
../testt.c \
../uart.c 

OBJS += \
./ADC.o \
./gpio.o \
./lcd.o \
./motor.o \
./temp.o \
./testt.o \
./uart.o 

C_DEPS += \
./ADC.d \
./gpio.d \
./lcd.d \
./motor.d \
./temp.d \
./testt.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


