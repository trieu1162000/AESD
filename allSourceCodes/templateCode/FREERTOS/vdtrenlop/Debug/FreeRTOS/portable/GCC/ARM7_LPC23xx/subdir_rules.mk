################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/GCC/ARM7_LPC23xx/%.obj: ../FreeRTOS/portable/GCC/ARM7_LPC23xx/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1020/ccs/tools/compiler/ti-cgt-arm_20.2.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --include_path="D:/EmbeddedProgExample/vdtrenlop/FreeRTOS/include" --include_path="D:/EmbeddedProgExample/vdtrenlop/FreeRTOS" --include_path="D:/EmbeddedProgExample/vdtrenlop/Application" --include_path="D:/EmbeddedProgExample/vdtrenlop" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccs1020/ccs/tools/compiler/ti-cgt-arm_20.2.2.LTS/include" --define=ccs="ccs" --define=TARGET_IS_BLIZZARD_RB1 --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="FreeRTOS/portable/GCC/ARM7_LPC23xx/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS/portable/GCC/ARM7_LPC23xx" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


