################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Link/%.o: ../Link/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c29_2.0.0.STS/bin/c29clang.exe" -c -march=c0 -mcpu=c29.c0 -O0 -I"C:/ti/f29h85x-sdk_1_02_01_00/source" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/security" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/driverlib" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/calibration/hrpwm/include" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/bitfields" -I"C:/ti/f29h85x-sdk_1_02_01_00/examples/device_support/include" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/rtlibs/dcl" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/rtlibs/dcl/common" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/rtlibs/dcl/df" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/rtlibs/dcl/misc" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/rtlibs/dcl/pi" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/rtlibs/dcl/pid" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/rtlibs/dsp/fpu/fpu32/fft" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/rtlibs/dsp/fpu/fpu32/fir" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/rtlibs/dsp/fpu/fpu32/iir" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/rtlibs/fastmath/crc" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/rtlibs/fastmath/matrix" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/rtlibs/fastmath/binary_lut_search" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/rtlibs/iqmath" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/kernel/freertos/Source/include" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/kernel/freertos/Source/portable/CCS/C2000_C29x" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/flash_api/include/FlashAPI" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/kernel/dpl" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/pmic" -I"C:/ti/f29h85x-sdk_1_02_01_00/source/sdl" -I"C:/Users/Silicium Lab/workspace_ccstheia/TP1_PDSTR" -I"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c29_2.0.0.STS/include" -DDEBUG -gdwarf-3 -Qunused-arguments -MMD -MP -MF"Link/$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/Users/Silicium Lab/workspace_ccstheia/TP1_PDSTR/RAM/syscfg"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


