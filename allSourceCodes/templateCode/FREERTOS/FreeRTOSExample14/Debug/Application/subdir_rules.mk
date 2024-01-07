################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Application/%.obj: ../Application/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/CODE COMPOSER STUDIO/FREERTOS/FreeRTOSExample14" --include_path="C:/Users/Dell/Desktop/EmbeddedProgExample/EmbeddedProgExample/FreeRTOSExample14/FreeRTOSSource" --include_path="C:/Users/Dell/Desktop/EmbeddedProgExample/EmbeddedProgExample/FreeRTOSExample14/drivers" --include_path="C:/Users/Dell/Desktop/EmbeddedProgExample/EmbeddedProgExample/FreeRTOSExample14" --include_path="C:/Users/Dell/Desktop/EmbeddedProgExample/EmbeddedProgExample/FreeRTOSExample14/Application" --include_path="C:/Users/Dell/Desktop/viduFreeRTOS/vdtrenlop/FreeRTOS/include" --include_path="C:/ti/TivaWare_C_Series-2.2.0.295" --include_path="D:/TIVAWARE" --include_path="D:/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_BLIZZARD_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Application/$(basename $(<F)).d_raw" --obj_directory="Application" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


