################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/SensorBME280/BME280Config/BME280Config.c 

OBJS += \
./src/SensorBME280/BME280Config/BME280Config.o 

C_DEPS += \
./src/SensorBME280/BME280Config/BME280Config.d 


# Each subdirectory must supply rules for building sources it contributes
src/SensorBME280/BME280Config/BME280Config.o: ../src/SensorBME280/BME280Config/BME280Config.c src/SensorBME280/BME280Config/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32BG22C224F512IM40=1' '-DSL_BOARD_NAME="BRD4184A"' '-DSL_BOARD_REV="A02"' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DMBEDTLS_CONFIG_FILE=<sl_mbedtls_config.h>' '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=0' '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>' '-DSLI_RADIOAES_REQUIRES_MASKING=1' -I"C:\development\METEO\Meteo\src\timer" -I"C:\development\METEO\Meteo\src\usart" -I"C:\development\METEO\Meteo\packages\BME280" -I"C:\development\METEO\Meteo\src\ble" -I"C:\development\METEO\Meteo\src\i2c" -I"C:\development\METEO\Meteo\src\SensorWind" -I"C:\development\METEO\Meteo\src\SensorBME280" -I"C:\development\METEO\Meteo\config" -I"C:\development\METEO\Meteo\config\btconf" -I"C:\development\METEO\Meteo" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\Device\SiliconLabs\EFR32BG22\Include" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\app\common\util\app_assert" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\common\inc" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\protocol\bluetooth\inc" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\hardware\board\inc" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\CMSIS\Core\Include" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\security\sl_component\sl_cryptoacc_library\include" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\security\sl_component\sl_cryptoacc_library\src" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\service\device_init\inc" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\emdrv\common\inc" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\emlib\inc" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\app\bluetooth\common\gatt_service_device_information" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\service\hfxo_manager\inc" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\security\sl_component\sl_mbedtls_support\config" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\security\sl_component\sl_mbedtls_support\inc" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\util\third_party\mbedtls\include" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\util\third_party\mbedtls\library" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\service\mpu\inc" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\hardware\driver\mx25_flash_shutdown\inc\sl_mx25_flash_shutdown_usart" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\emdrv\nvm3\inc" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\service\power_manager\inc" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\security\sl_component\sl_psa_driver\inc" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\security\sl_component\sl_psa_driver\inc\public" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\radio\rail_lib\common" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\radio\rail_lib\protocol\ble" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\radio\rail_lib\protocol\ieee802154" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\radio\rail_lib\protocol\zwave" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\radio\rail_lib\chip\efr32\efr32xg2x" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\radio\rail_lib\plugin\pa-conversions" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\radio\rail_lib\plugin\pa-conversions\efr32xg22" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\radio\rail_lib\plugin\rail_util_pti" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\security\sl_component\se_manager\inc" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\security\sl_component\se_manager\src" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\util\silicon_labs\silabs_core\memory_manager" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\common\toolchain\inc" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\service\system\inc" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\service\sleeptimer\inc" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\security\sl_component\sl_protocol_crypto\src" -I"C:\development\METEO\Meteo\gecko_sdk_4.2.0\platform\service\udelay\inc" -I"C:\development\METEO\Meteo\autogen" -O0 -Wall -Wextra -fomit-frame-pointer -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mcmse --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"src/SensorBME280/BME280Config/BME280Config.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


