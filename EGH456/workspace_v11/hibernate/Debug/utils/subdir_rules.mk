################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
utils/cmdline.obj: C:/ti/tivaware_c_series_2_1_4_178/utils/cmdline.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1020/ccs/tools/compiler/ti-cgt-arm_20.2.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="C:/ti/ccs1020/ccs/tools/compiler/ti-cgt-arm_20.2.2.LTS/include" --include_path="C:/Users/n9996095/OneDrive - Queensland University of Technology/Documents/EGH456/workspace_v11/hibernate" --include_path="C:/ti/tivaware_c_series_2_1_4_178/examples/boards/ek-tm4c1294xl" --include_path="C:/ti/tivaware_c_series_2_1_4_178" --advice:power=all -g --gcc --define=ccs="ccs" --define=PART_TM4C1294NCPDT --define=TARGET_IS_TM4C129_RA0 --define=SNOWFLAKE --define=UART_BUFFERED --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="utils/cmdline.d_raw" --obj_directory="utils" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

utils/uartstdio.obj: C:/ti/tivaware_c_series_2_1_4_178/utils/uartstdio.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1020/ccs/tools/compiler/ti-cgt-arm_20.2.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="C:/ti/ccs1020/ccs/tools/compiler/ti-cgt-arm_20.2.2.LTS/include" --include_path="C:/Users/n9996095/OneDrive - Queensland University of Technology/Documents/EGH456/workspace_v11/hibernate" --include_path="C:/ti/tivaware_c_series_2_1_4_178/examples/boards/ek-tm4c1294xl" --include_path="C:/ti/tivaware_c_series_2_1_4_178" --advice:power=all -g --gcc --define=ccs="ccs" --define=PART_TM4C1294NCPDT --define=TARGET_IS_TM4C129_RA0 --define=SNOWFLAKE --define=UART_BUFFERED --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="utils/uartstdio.d_raw" --obj_directory="utils" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

utils/ustdlib.obj: C:/ti/tivaware_c_series_2_1_4_178/utils/ustdlib.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs1020/ccs/tools/compiler/ti-cgt-arm_20.2.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="C:/ti/ccs1020/ccs/tools/compiler/ti-cgt-arm_20.2.2.LTS/include" --include_path="C:/Users/n9996095/OneDrive - Queensland University of Technology/Documents/EGH456/workspace_v11/hibernate" --include_path="C:/ti/tivaware_c_series_2_1_4_178/examples/boards/ek-tm4c1294xl" --include_path="C:/ti/tivaware_c_series_2_1_4_178" --advice:power=all -g --gcc --define=ccs="ccs" --define=PART_TM4C1294NCPDT --define=TARGET_IS_TM4C129_RA0 --define=SNOWFLAKE --define=UART_BUFFERED --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="utils/ustdlib.d_raw" --obj_directory="utils" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


