################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := E:/Apps/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./tm4c123gh6pm_startup_ccs.obj" \
"./Application/freertos_demo.obj" \
"./FreeRTOSSource/croutine.obj" \
"./FreeRTOSSource/event_groups.obj" \
"./FreeRTOSSource/heap_4.obj" \
"./FreeRTOSSource/list.obj" \
"./FreeRTOSSource/port.obj" \
"./FreeRTOSSource/portasm.obj" \
"./FreeRTOSSource/queue.obj" \
"./FreeRTOSSource/stream_buffer.obj" \
"./FreeRTOSSource/tasks.obj" \
"./FreeRTOSSource/timers.obj" \
"./drivers/uartstdio.obj" \
"./my_libs/src/actions_api.obj" \
"./my_libs/src/configure_peripherals_api.obj" \
"./my_libs/src/eeprom_api.obj" \
"./my_libs/src/lcd_i2c_api.obj" \
"./my_libs/src/leds_buzzer_lock.obj" \
"./my_libs/src/queue_cards_api.obj" \
"./my_libs/src/rc522_api.obj" \
"./my_libs/src/system_FSM_api.obj" \
"./my_libs/src/timer_handler_api.obj" \
"./my_libs/src/uart_api.obj" \
"E:/Apps/ti/TivaWare_C_Series-2.2.0.295/driverlib/ccs/Debug/driverlib.lib" \
"../tm4c123gh6pm.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Application/subdir_vars.mk
-include FreeRTOSSource/subdir_vars.mk
-include drivers/subdir_vars.mk
-include my_libs/src/subdir_vars.mk
-include subdir_rules.mk
-include Application/subdir_rules.mk
-include FreeRTOSSource/subdir_rules.mk
-include drivers/subdir_rules.mk
-include my_libs/src/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
FreeRTOSExample7.out \

EXE_OUTPUTS__QUOTED += \
"FreeRTOSExample7.out" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "FreeRTOSExample7.out"

# Tool invocations
FreeRTOSExample7.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"E:/Apps/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_BLIZZARD_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"FreeRTOSExample7.map" --heap_size=2000 --stack_size=14000 -i"E:/Apps/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/lib" -i"E:/Apps/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="FreeRTOSExample7_linkInfo.xml" --rom_model -o "FreeRTOSExample7.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "tm4c123gh6pm_startup_ccs.obj" "Application\freertos_demo.obj" "FreeRTOSSource\croutine.obj" "FreeRTOSSource\event_groups.obj" "FreeRTOSSource\heap_4.obj" "FreeRTOSSource\list.obj" "FreeRTOSSource\port.obj" "FreeRTOSSource\portasm.obj" "FreeRTOSSource\queue.obj" "FreeRTOSSource\stream_buffer.obj" "FreeRTOSSource\tasks.obj" "FreeRTOSSource\timers.obj" "drivers\uartstdio.obj" "my_libs\src\actions_api.obj" "my_libs\src\configure_peripherals_api.obj" "my_libs\src\eeprom_api.obj" "my_libs\src\lcd_i2c_api.obj" "my_libs\src\leds_buzzer_lock.obj" "my_libs\src\queue_cards_api.obj" "my_libs\src\rc522_api.obj" "my_libs\src\system_FSM_api.obj" "my_libs\src\timer_handler_api.obj" "my_libs\src\uart_api.obj" 
	-$(RM) "tm4c123gh6pm_startup_ccs.d" "Application\freertos_demo.d" "FreeRTOSSource\croutine.d" "FreeRTOSSource\event_groups.d" "FreeRTOSSource\heap_4.d" "FreeRTOSSource\list.d" "FreeRTOSSource\port.d" "FreeRTOSSource\queue.d" "FreeRTOSSource\stream_buffer.d" "FreeRTOSSource\tasks.d" "FreeRTOSSource\timers.d" "drivers\uartstdio.d" "my_libs\src\actions_api.d" "my_libs\src\configure_peripherals_api.d" "my_libs\src\eeprom_api.d" "my_libs\src\lcd_i2c_api.d" "my_libs\src\leds_buzzer_lock.d" "my_libs\src\queue_cards_api.d" "my_libs\src\rc522_api.d" "my_libs\src\system_FSM_api.d" "my_libs\src\timer_handler_api.d" "my_libs\src\uart_api.d" 
	-$(RM) "FreeRTOSSource\portasm.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

