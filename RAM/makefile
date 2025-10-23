################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c29_2.0.0.STS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./syscfg/board.o" \
"./syscfg/device.o" \
"./syscfg/ti_drivers_config.o" \
"./syscfg/ti_dpl_config.o" \
"./TP_dds.o" \
"./TP_sine_table.o" \
"./main.o" \
"./Link/Link.o" \
"./Link/Link_Func.o" \
"./device/bitfield_structs.o" \
"./device/codestartbranch.o" \
"../f29h85x_ram_lnk.cmd" \
$(GEN_CMDS__FLAG) \
-Wl,-ldriverlib.lib \
-Wl,-lsfo.lib \
-Wl,-lF29H85x_NWFlashAPI_v21.00.00.00.lib \
-Wl,-lsecurity_drivers.lib \
-Wl,-ldpl_nortos.lib \
-Wl,-lsdl_debug.lib \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Link/subdir_vars.mk
-include device/subdir_vars.mk
-include subdir_rules.mk
-include Link/subdir_rules.mk
-include device/subdir_rules.mk
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
TP1_PDSTR.out 

EXE_OUTPUTS__QUOTED += \
"TP1_PDSTR.out" 


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "TP1_PDSTR.out"

# Tool invocations
TP1_PDSTR.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c29_2.0.0.STS/bin/c29clang.exe" -march=c0 -mcpu=c29.c0 -O0 -DDEBUG -gdwarf-3 -Qunused-arguments -Wl,-m"TP1_PDSTR.map" -Wl,--heap_size=0x400 -Wl,--stack_size=0x2000 -Wl,-i"C:/ti/f29h85x-sdk_1_02_01_00/source/driverlib/ccs" -Wl,-i"C:/ti/f29h85x-sdk_1_02_01_00/source/flash_api/lib" -Wl,-i"C:/ti/f29h85x-sdk_1_02_01_00/source/calibration/hrpwm/lib" -Wl,-i"C:/ti/f29h85x-sdk_1_02_01_00/source/security/ccs" -Wl,-i"C:/ti/f29h85x-sdk_1_02_01_00/source/kernel/nortos/ccs" -Wl,-i"C:/ti/f29h85x-sdk_1_02_01_00/source/sdl/ccs" -Wl,-i"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c29_2.0.0.STS/lib" -Wl,--reread_libs -Wl,--diag_suppress=10325-D -Wl,--diag_suppress=10063-D -Wl,--diag_wrap=off -Wl,--display_error_number -Wl,--warn_sections -Wl,--xml_link_info="TP1_PDSTR_linkInfo.xml" -Wl,--rom_model -o "TP1_PDSTR.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(GEN_MISC_FILES__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "syscfg\board.o" "syscfg\device.o" "syscfg\ti_drivers_config.o" "syscfg\ti_dpl_config.o" "TP_dds.o" "TP_sine_table.o" "main.o" "Link\Link.o" "Link\Link_Func.o" "device\bitfield_structs.o" "device\codestartbranch.o" 
	-$(RM) "syscfg\board.d" "syscfg\device.d" "syscfg\ti_drivers_config.d" "syscfg\ti_dpl_config.d" "TP_dds.d" "TP_sine_table.d" "main.d" "Link\Link.d" "Link\Link_Func.d" "device\bitfield_structs.d" 
	-$(RM) "device\codestartbranch.d" 
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c29_2.0.0.STS/bin/c29objcopy.exe -O binary TP1_PDSTR.out TP1_PDSTR.bin
	-$(call IF_EQUAL_OPEN, 1, 0) $(PYTHON) C:/ti/f29h85x-sdk_1_02_01_00/tools/boot/signing/mcu_rom_image_gen.py --image-bin TP1_PDSTR.bin --core C29 --swrv 1 --loadaddr 0x200E1000 --sign-key C:/ti/f29h85x-sdk_1_02_01_00/tools/boot/signing/mcu_gpkey.pem --out-image TP1_PDSTR_cert.bin --device f29h85x --boot RAM --img_integ no $(IF_EQUAL_CLOSE)
	-$(call IF_EQUAL_OPEN, 1, 1) C:/ti/f29h85x-sdk_1_02_01_00/tools/misc/$(UPDATEDUMMYCERT) $(DUMMY_CERT_RAM) TP1_PDSTR.bin $(IF_EQUAL_CLOSE)
	-$(call IF_EQUAL_OPEN, 1, 1) $(CONCAT) $(DUMMY_CERT_RAM) TP1_PDSTR.bin > TP1_PDSTR_cert.bin $(IF_EQUAL_CLOSE)
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

