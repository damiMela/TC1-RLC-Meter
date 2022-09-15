################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../OwnDrivers/freq_boton.c \
../OwnDrivers/sine_generator.c 

OBJS += \
./OwnDrivers/freq_boton.o \
./OwnDrivers/sine_generator.o 

C_DEPS += \
./OwnDrivers/freq_boton.d \
./OwnDrivers/sine_generator.d 


# Each subdirectory must supply rules for building sources it contributes
OwnDrivers/%.o: ../OwnDrivers/%.c OwnDrivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_LPC845M301JBD48 -DCPU_LPC845M301JBD48_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"/home/juan/Documentos/UTN/TC1/Proyecto/LPC845/Sine_generator_DAC_DMA/board" -I"/home/juan/Documentos/UTN/TC1/Proyecto/LPC845/Sine_generator_DAC_DMA/OwnDrivers" -I"/home/juan/Documentos/UTN/TC1/Proyecto/LPC845/Sine_generator_DAC_DMA/source" -I"/home/juan/Documentos/UTN/TC1/Proyecto/LPC845/Sine_generator_DAC_DMA/drivers" -I"/home/juan/Documentos/UTN/TC1/Proyecto/LPC845/Sine_generator_DAC_DMA/component/uart" -I"/home/juan/Documentos/UTN/TC1/Proyecto/LPC845/Sine_generator_DAC_DMA/utilities" -I"/home/juan/Documentos/UTN/TC1/Proyecto/LPC845/Sine_generator_DAC_DMA/CMSIS" -I"/home/juan/Documentos/UTN/TC1/Proyecto/LPC845/Sine_generator_DAC_DMA/device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


