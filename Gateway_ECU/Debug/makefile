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
Gateway_ECU.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Gateway_ECU.list \

OBJCOPY_HEX += \
Gateway_ECU.hex \

OBJCOPY_BIN += \
Gateway_ECU.bin \


# All Target
all: Gateway_ECU.elf secondary-outputs

# Tool invocations
Gateway_ECU.elf: $(OBJS) $(USER_OBJS) D:\Eme\ARM\projects\drivers_withConfig\CAN_transmitter\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "Gateway_ECU.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\Eme\ARM\projects\drivers_withConfig\CAN_transmitter\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Gateway_ECU.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Gateway_ECU.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Gateway_ECU.list"
	@echo 'Finished building: $@'
	@echo ' '

Gateway_ECU.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Gateway_ECU.hex"
	@echo 'Finished building: $@'
	@echo ' '

Gateway_ECU.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Gateway_ECU.bin"
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
