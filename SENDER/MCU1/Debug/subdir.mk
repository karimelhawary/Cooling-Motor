################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../E2PROM.c \
../gpio.c \
../motor.c \
../temp.c \
../test102.c \
../uart.c 

OBJS += \
./ADC.o \
./E2PROM.o \
./gpio.o \
./motor.o \
./temp.o \
./test102.o \
./uart.o 

C_DEPS += \
./ADC.d \
./E2PROM.d \
./gpio.d \
./motor.d \
./temp.d \
./test102.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


