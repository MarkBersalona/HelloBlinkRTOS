################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/mark/SimplicityStudio/SDKs/gecko_sdk/platform/emdrv/gpiointerrupt/src/gpiointerrupt.c 

OBJS += \
./gecko_sdk_4.3.2/platform/emdrv/gpiointerrupt/src/gpiointerrupt.o 

C_DEPS += \
./gecko_sdk_4.3.2/platform/emdrv/gpiointerrupt/src/gpiointerrupt.d 


# Each subdirectory must supply rules for building sources it contributes
gecko_sdk_4.3.2/platform/emdrv/gpiointerrupt/src/gpiointerrupt.o: /home/mark/SimplicityStudio/SDKs/gecko_sdk/platform/emdrv/gpiointerrupt/src/gpiointerrupt.c gecko_sdk_4.3.2/platform/emdrv/gpiointerrupt/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DMGM240PB32VNA=1' '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' '-DSL_BOARD_NAME="BRD2704A"' '-DSL_BOARD_REV="A00"' '-DconfigNUM_SDK_THREAD_LOCAL_STORAGE_POINTERS=2' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"/home/mark/SiLabsProjects/HelloBlinkRTOS/config" -I"/home/mark/SiLabsProjects/HelloBlinkRTOS/autogen" -I"/home/mark/SiLabsProjects/HelloBlinkRTOS" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//platform/Device/SiliconLabs/MGM24/Include" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//platform/common/inc" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//hardware/board/inc" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/Core/Include" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//util/third_party/cmsis_dsp/DSP/Include" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//util/third_party/cmsis_dsp/DSP/Include/dsp" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//platform/CMSIS/RTOS2/Include" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//hardware/driver/configuration_over_swo/inc" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//platform/driver/debug/inc" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//platform/service/device_init/inc" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/dmadrv/inc" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/common/inc" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//platform/emlib/inc" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//util/third_party/freertos/cmsis/Include" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//util/third_party/freertos/kernel/include" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//util/third_party/freertos/kernel/portable/GCC/ARM_CM33_NTZ/non_secure" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/gpiointerrupt/inc" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//platform/service/iostream/inc" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//platform/driver/leddrv/inc" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//platform/peripheral/inc" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//platform/common/toolchain/inc" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//platform/service/system/inc" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//platform/service/sleeptimer/inc" -I"/home/mark/SimplicityStudio/SDKs/gecko_sdk//platform/emdrv/uartdrv/inc" -Os -Wall -Wextra -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mcmse --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.3.2/platform/emdrv/gpiointerrupt/src/gpiointerrupt.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


