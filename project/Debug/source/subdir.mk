################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/ECE3140Lab2.c \
../source/led.c \
../source/main.c 

S_SRCS += \
../source/ECE3140_lowlevel.s \
../source/led_lowlevel.s 

C_DEPS += \
./source/ECE3140Lab2.d \
./source/led.d \
./source/main.d 

OBJS += \
./source/ECE3140Lab2.o \
./source/ECE3140_lowlevel.o \
./source/led.o \
./source/led_lowlevel.o \
./source/main.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFRDM_KL46Z -DFREEDOM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/Users/harshvardhan/Code/ece3140/final_project/project/source" -I"/Users/harshvardhan/Code/ece3140/final_project/project" -I"/Users/harshvardhan/Code/ece3140/final_project/project/CMSIS" -I"/Users/harshvardhan/Code/ece3140/final_project/project/drivers" -I"/Users/harshvardhan/Code/ece3140/final_project/project/CMSIS_driver" -I"/Users/harshvardhan/Code/ece3140/final_project/project/startup" -I"/Users/harshvardhan/Code/ece3140/final_project/project/utilities" -I"/Users/harshvardhan/Code/ece3140/final_project/project/board/src" -I"/Users/harshvardhan/Code/ece3140/final_project/project/board" -O0 -fno-common -g -gdwarf-4 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/%.o: ../source/%.s source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__REDLIB__ -I"/Users/harshvardhan/Code/ece3140/final_project/project/source" -I"/Users/harshvardhan/Code/ece3140/final_project/project" -I"/Users/harshvardhan/Code/ece3140/final_project/project/CMSIS" -I"/Users/harshvardhan/Code/ece3140/final_project/project/drivers" -I"/Users/harshvardhan/Code/ece3140/final_project/project/CMSIS_driver" -I"/Users/harshvardhan/Code/ece3140/final_project/project/startup" -I"/Users/harshvardhan/Code/ece3140/final_project/project/utilities" -I"/Users/harshvardhan/Code/ece3140/final_project/project/board/src" -I"/Users/harshvardhan/Code/ece3140/final_project/project/board" -g3 -gdwarf-4 -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -specs=redlib.specs -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/ECE3140Lab2.d ./source/ECE3140Lab2.o ./source/ECE3140_lowlevel.o ./source/led.d ./source/led.o ./source/led_lowlevel.o ./source/main.d ./source/main.o

.PHONY: clean-source

