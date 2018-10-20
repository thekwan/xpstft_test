################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
tft_test_1.elf.size \

ELFCHECK += \
tft_test_1.elf.elfcheck \


# All Target
all: tft_test_1.elf secondary-outputs

# Tool invocations
tft_test_1.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo Building target: $@
	@echo Invoking: PowerPC gcc linker
	powerpc-eabi-gcc -Wl,-T -Wl,../src/lscript.ld -L../../bootloader_bsp/ppc440_0/lib -mcpu=440 -o"tft_test_1.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo Finished building target: $@
	@echo ' '

tft_test_1.elf.size: tft_test_1.elf
	@echo Invoking: PowerPC Print Size
	powerpc-eabi-size tft_test_1.elf  |tee "tft_test_1.elf.size"
	@echo Finished building: $@
	@echo ' '

tft_test_1.elf.elfcheck: tft_test_1.elf
	@echo Invoking: Xilinx ELF Check
	elfcheck tft_test_1.elf -hw ../../ppc_linux_lcd3_hw_platform/system.xml -pe ppc440_0  |tee "tft_test_1.elf.elfcheck"
	@echo Finished building: $@
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) tft_test_1.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
