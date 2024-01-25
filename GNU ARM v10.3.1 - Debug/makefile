################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include gecko_sdk_4.3.2/util/third_party/freertos/kernel/portable/MemMang/subdir.mk
-include gecko_sdk_4.3.2/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/subdir.mk
-include gecko_sdk_4.3.2/util/third_party/freertos/kernel/subdir.mk
-include gecko_sdk_4.3.2/util/third_party/freertos/cmsis/Source/subdir.mk
-include gecko_sdk_4.3.2/util/third_party/aws_iot_libs/vendors/siliconlabs/boards/all/ports/common_io/iot_watchdog/source/subdir.mk
-include gecko_sdk_4.3.2/platform/service/system/src/subdir.mk
-include gecko_sdk_4.3.2/platform/service/sleeptimer/src/subdir.mk
-include gecko_sdk_4.3.2/platform/service/iostream/src/subdir.mk
-include gecko_sdk_4.3.2/platform/service/device_init/src/subdir.mk
-include gecko_sdk_4.3.2/platform/peripheral/src/subdir.mk
-include gecko_sdk_4.3.2/platform/emlib/src/subdir.mk
-include gecko_sdk_4.3.2/platform/emdrv/uartdrv/src/subdir.mk
-include gecko_sdk_4.3.2/platform/emdrv/gpiointerrupt/src/subdir.mk
-include gecko_sdk_4.3.2/platform/emdrv/dmadrv/src/subdir.mk
-include gecko_sdk_4.3.2/platform/driver/leddrv/src/subdir.mk
-include gecko_sdk_4.3.2/platform/driver/debug/src/subdir.mk
-include gecko_sdk_4.3.2/platform/common/toolchain/src/subdir.mk
-include gecko_sdk_4.3.2/platform/common/src/subdir.mk
-include gecko_sdk_4.3.2/platform/Device/SiliconLabs/MGM24/Source/subdir.mk
-include gecko_sdk_4.3.2/platform/CMSIS/RTOS2/Source/subdir.mk
-include gecko_sdk_4.3.2/hardware/driver/configuration_over_swo/src/subdir.mk
-include gecko_sdk_4.3.2/hardware/board/src/subdir.mk
-include autogen/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := HelloBlinkRTOS
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: HelloBlinkRTOS.axf

# Tool invocations
HelloBlinkRTOS.axf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -T "/home/mark/SiLabsProjects/HelloBlinkRTOS/autogen/linkerfile.ld" -Xlinker --gc-sections -Xlinker -Map="HelloBlinkRTOS.map" -mfpu=fpv5-sp-d16 -mfloat-abi=hard --specs=nano.specs -o HelloBlinkRTOS.axf -Wl,--start-group "./app.o" "./main.o" "./autogen/iot_watchdog_desc.o" "./autogen/sl_board_default_init.o" "./autogen/sl_device_init_clocks.o" "./autogen/sl_event_handler.o" "./autogen/sl_iostream_handles.o" "./autogen/sl_iostream_init_usart_instances.o" "./autogen/sl_simple_led_instances.o" "./gecko_sdk_4.3.2/hardware/board/src/sl_board_control_gpio.o" "./gecko_sdk_4.3.2/hardware/board/src/sl_board_init.o" "./gecko_sdk_4.3.2/hardware/driver/configuration_over_swo/src/sl_cos.o" "./gecko_sdk_4.3.2/platform/CMSIS/RTOS2/Source/os_systick.o" "./gecko_sdk_4.3.2/platform/Device/SiliconLabs/MGM24/Source/startup_mgm24.o" "./gecko_sdk_4.3.2/platform/Device/SiliconLabs/MGM24/Source/system_mgm24.o" "./gecko_sdk_4.3.2/platform/common/src/sl_assert.o" "./gecko_sdk_4.3.2/platform/common/src/sl_string.o" "./gecko_sdk_4.3.2/platform/common/src/sli_cmsis_os2_ext_task_register.o" "./gecko_sdk_4.3.2/platform/common/toolchain/src/sl_memory.o" "./gecko_sdk_4.3.2/platform/driver/debug/src/sl_debug_swo.o" "./gecko_sdk_4.3.2/platform/driver/leddrv/src/sl_led.o" "./gecko_sdk_4.3.2/platform/driver/leddrv/src/sl_simple_led.o" "./gecko_sdk_4.3.2/platform/emdrv/dmadrv/src/dmadrv.o" "./gecko_sdk_4.3.2/platform/emdrv/gpiointerrupt/src/gpiointerrupt.o" "./gecko_sdk_4.3.2/platform/emdrv/uartdrv/src/uartdrv.o" "./gecko_sdk_4.3.2/platform/emlib/src/em_burtc.o" "./gecko_sdk_4.3.2/platform/emlib/src/em_cmu.o" "./gecko_sdk_4.3.2/platform/emlib/src/em_core.o" "./gecko_sdk_4.3.2/platform/emlib/src/em_emu.o" "./gecko_sdk_4.3.2/platform/emlib/src/em_eusart.o" "./gecko_sdk_4.3.2/platform/emlib/src/em_gpio.o" "./gecko_sdk_4.3.2/platform/emlib/src/em_ldma.o" "./gecko_sdk_4.3.2/platform/emlib/src/em_msc.o" "./gecko_sdk_4.3.2/platform/emlib/src/em_prs.o" "./gecko_sdk_4.3.2/platform/emlib/src/em_system.o" "./gecko_sdk_4.3.2/platform/emlib/src/em_timer.o" "./gecko_sdk_4.3.2/platform/emlib/src/em_usart.o" "./gecko_sdk_4.3.2/platform/emlib/src/em_wdog.o" "./gecko_sdk_4.3.2/platform/peripheral/src/peripheral_sysrtc.o" "./gecko_sdk_4.3.2/platform/service/device_init/src/sl_device_init_dcdc_s2.o" "./gecko_sdk_4.3.2/platform/service/device_init/src/sl_device_init_emu_s2.o" "./gecko_sdk_4.3.2/platform/service/device_init/src/sl_device_init_hfxo_mgm24.o" "./gecko_sdk_4.3.2/platform/service/device_init/src/sl_device_init_nvic.o" "./gecko_sdk_4.3.2/platform/service/iostream/src/sl_iostream.o" "./gecko_sdk_4.3.2/platform/service/iostream/src/sl_iostream_uart.o" "./gecko_sdk_4.3.2/platform/service/iostream/src/sl_iostream_usart.o" "./gecko_sdk_4.3.2/platform/service/sleeptimer/src/sl_sleeptimer.o" "./gecko_sdk_4.3.2/platform/service/sleeptimer/src/sl_sleeptimer_hal_burtc.o" "./gecko_sdk_4.3.2/platform/service/sleeptimer/src/sl_sleeptimer_hal_sysrtc.o" "./gecko_sdk_4.3.2/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.o" "./gecko_sdk_4.3.2/platform/service/system/src/sl_system_init.o" "./gecko_sdk_4.3.2/platform/service/system/src/sl_system_kernel.o" "./gecko_sdk_4.3.2/util/third_party/aws_iot_libs/vendors/siliconlabs/boards/all/ports/common_io/iot_watchdog/source/iot_watchdog_drv.o" "./gecko_sdk_4.3.2/util/third_party/aws_iot_libs/vendors/siliconlabs/boards/all/ports/common_io/iot_watchdog/source/iot_watchdog_hal.o" "./gecko_sdk_4.3.2/util/third_party/freertos/cmsis/Source/cmsis_os2.o" "./gecko_sdk_4.3.2/util/third_party/freertos/kernel/croutine.o" "./gecko_sdk_4.3.2/util/third_party/freertos/kernel/event_groups.o" "./gecko_sdk_4.3.2/util/third_party/freertos/kernel/list.o" "./gecko_sdk_4.3.2/util/third_party/freertos/kernel/queue.o" "./gecko_sdk_4.3.2/util/third_party/freertos/kernel/stream_buffer.o" "./gecko_sdk_4.3.2/util/third_party/freertos/kernel/tasks.o" "./gecko_sdk_4.3.2/util/third_party/freertos/kernel/timers.o" "./gecko_sdk_4.3.2/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/port.o" "./gecko_sdk_4.3.2/util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.o" "./gecko_sdk_4.3.2/util/third_party/freertos/kernel/portable/MemMang/heap_4.o" "/home/mark/SimplicityStudio/SDKs/gecko_sdk//util/third_party/cmsis_dsp/libs/GCC/cortex-m33/libCMSISDSPBasicMath.a" "/home/mark/SimplicityStudio/SDKs/gecko_sdk//util/third_party/cmsis_dsp/libs/GCC/cortex-m33/libCMSISDSPBayes.a" "/home/mark/SimplicityStudio/SDKs/gecko_sdk//util/third_party/cmsis_dsp/libs/GCC/cortex-m33/libCMSISDSPCommon.a" "/home/mark/SimplicityStudio/SDKs/gecko_sdk//util/third_party/cmsis_dsp/libs/GCC/cortex-m33/libCMSISDSPComplexMath.a" "/home/mark/SimplicityStudio/SDKs/gecko_sdk//util/third_party/cmsis_dsp/libs/GCC/cortex-m33/libCMSISDSPController.a" "/home/mark/SimplicityStudio/SDKs/gecko_sdk//util/third_party/cmsis_dsp/libs/GCC/cortex-m33/libCMSISDSPDistance.a" "/home/mark/SimplicityStudio/SDKs/gecko_sdk//util/third_party/cmsis_dsp/libs/GCC/cortex-m33/libCMSISDSPFastMath.a" "/home/mark/SimplicityStudio/SDKs/gecko_sdk//util/third_party/cmsis_dsp/libs/GCC/cortex-m33/libCMSISDSPFiltering.a" "/home/mark/SimplicityStudio/SDKs/gecko_sdk//util/third_party/cmsis_dsp/libs/GCC/cortex-m33/libCMSISDSPInterpolation.a" "/home/mark/SimplicityStudio/SDKs/gecko_sdk//util/third_party/cmsis_dsp/libs/GCC/cortex-m33/libCMSISDSPMatrix.a" "/home/mark/SimplicityStudio/SDKs/gecko_sdk//util/third_party/cmsis_dsp/libs/GCC/cortex-m33/libCMSISDSPQuaternionMath.a" "/home/mark/SimplicityStudio/SDKs/gecko_sdk//util/third_party/cmsis_dsp/libs/GCC/cortex-m33/libCMSISDSPStatistics.a" "/home/mark/SimplicityStudio/SDKs/gecko_sdk//util/third_party/cmsis_dsp/libs/GCC/cortex-m33/libCMSISDSPSupport.a" "/home/mark/SimplicityStudio/SDKs/gecko_sdk//util/third_party/cmsis_dsp/libs/GCC/cortex-m33/libCMSISDSPSVM.a" "/home/mark/SimplicityStudio/SDKs/gecko_sdk//util/third_party/cmsis_dsp/libs/GCC/cortex-m33/libCMSISDSPTransform.a" -lgcc -lc -lm -lnosys -Wl,--end-group -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building out file: HelloBlinkRTOS.out'
	arm-none-eabi-objcopy "HelloBlinkRTOS.axf" "HelloBlinkRTOS.out"
	@echo ' '

	@echo 'Building hex file: HelloBlinkRTOS.hex'
	arm-none-eabi-objcopy -O ihex "HelloBlinkRTOS.axf" "HelloBlinkRTOS.hex"
	@echo ' '

	@echo 'Building bin file: HelloBlinkRTOS.bin'
	arm-none-eabi-objcopy -O binary "HelloBlinkRTOS.axf" "HelloBlinkRTOS.bin"
	@echo ' '

	@echo 'Building s37 file: HelloBlinkRTOS.s37'
	arm-none-eabi-objcopy -O srec "HelloBlinkRTOS.axf" "HelloBlinkRTOS.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "HelloBlinkRTOS.axf" -A
	@echo ' '

# Other Targets
clean:
	-@$(foreach FILE, $(EXECUTABLES), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(OBJS), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(C_DEPS), $(shell $(RM) $(FILE)) )
	-$(RM) HelloBlinkRTOS.axf
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets
