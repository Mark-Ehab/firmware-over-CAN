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
CAN_Receive.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
CAN_Receive.list \

OBJCOPY_HEX += \
CAN_Receive.hex \

OBJCOPY_BIN += \
CAN_Receive.bin \


# All Target
all: CAN_Receive.elf secondary-outputs

# Tool invocations
CAN_Receive.elf: $(OBJS) $(USER_OBJS) D:\Eme\ARM\projects\drivers_withConfig\CAN_Receive\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "CAN_Receive.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\Eme\ARM\projects\drivers_withConfig\CAN_Receive\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="CAN_Receive.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

CAN_Receive.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "CAN_Receive.list"
	@echo 'Finished building: $@'
	@echo ' '

CAN_Receive.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "CAN_Receive.hex"
	@echo 'Finished building: $@'
	@echo ' '

CAN_Receive.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "CAN_Receive.bin"
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
