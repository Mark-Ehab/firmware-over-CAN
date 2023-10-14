################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Main_ECU.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Main_ECU.list \

OBJCOPY_HEX += \
Main_ECU.hex \

OBJCOPY_BIN += \
Main_ECU.bin \


# All Target
all: Main_ECU.elf secondary-outputs

# Tool invocations
Main_ECU.elf: $(OBJS) $(USER_OBJS) D:\Eme\ARM\projects\drivers_withConfig\CAN_Receive\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "Main_ECU.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\Eme\ARM\projects\drivers_withConfig\CAN_Receive\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Main_ECU.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Main_ECU.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Main_ECU.list"
	@echo 'Finished building: $@'
	@echo ' '

Main_ECU.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Main_ECU.hex"
	@echo 'Finished building: $@'
	@echo ' '

Main_ECU.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Main_ECU.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
