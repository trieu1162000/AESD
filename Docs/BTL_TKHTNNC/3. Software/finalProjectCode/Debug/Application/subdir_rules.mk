################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Application/%.obj: ../Application/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"E:/Apps/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="E:/Old Data from Dell/1.2/BTVN2/BTVN2" --include_path="E:/Old Data from Dell/1.2/BTVN2/BTVN2/FreeRTOSSource" --include_path="E:/Old Data from Dell/1.2/BTVN2/BTVN2/drivers" --include_path="E:/Old Data from Dell/1.2/BTVN2/BTVN2/Application" --include_path="E:/Old Data from Dell/1.2/CODE COMPOSER STUDIO/FREERTOS/vdtrenlop/FreeRTOS/include" --include_path="E:/Apps/ti/TivaWare_C_Series-2.2.0.295" --include_path="E:/Apps/ti/TivaWare_C_Series-2.2.0.295" --include_path="E:/Apps/ti/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_BLIZZARD_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Application/$(basename $(<F)).d_raw" --obj_directory="Application" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


