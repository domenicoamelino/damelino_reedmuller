################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/PUF_extraction.c \
../src/Spongent.c \
../src/damelino_reedmuller.c \
../src/reedmuller.c \
../src/utilities.c 

OBJS += \
./src/PUF_extraction.o \
./src/Spongent.o \
./src/damelino_reedmuller.o \
./src/reedmuller.o \
./src/utilities.o 

C_DEPS += \
./src/PUF_extraction.d \
./src/Spongent.d \
./src/damelino_reedmuller.d \
./src/reedmuller.d \
./src/utilities.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


