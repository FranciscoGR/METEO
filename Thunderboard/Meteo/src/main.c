/***************************************************************************//**
 * @file
 * @brief main() function.
 ******************************************************************************/
#include "sl_component_catalog.h"
#include "sl_system_init.h"
#include "sl_power_manager.h"
#include "sl_system_process_action.h"
#include "sl_udelay.h"

#include "i2c.h"
#include "SensorBME280.h"
#include "BME280Config/BME280Config.h"
#include "SensorWind.h"
#include "usart.h"
#include "ble.h"
#include "timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TEMPERATUE_OFFSET   4.0

/* BME680 data structure*/
static bme280_t bme;
static float windSpeed;

int main(void)
{
  bool BMENewData = false, windNewData = false;

  /* Initialize Silicon Labs device, system, service(s) and protocol stack(s).
   * Note that if the kernel is present, processing task(s) will be created by
   * this call.
   */
  sl_system_init();

  /* Initialize BME280 sensor*/
  SensorBME280_init(&bme);

  /* Initialize wind speed sensor*/
  SensorWind_init();

  /* Initialize sensors data */
  bme.sensor_data.temperature = 0.0;
  bme.sensor_data.humidity = 0.0;
  windSpeed = 0x00;

  BMENewData = true;
  windNewData = true;

  /* Set Energy Mode 1 requirement to have USART available*/
  sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);

  while (1) {
    /* Do not remove this call: Silicon Labs components process action routine
     * must be called from the super loop.
     */
    sl_system_process_action();

    /* If device connected*/
    if(ble_getStatus() == BLE_STATUS_CONNECTED){
        if(!timer_isRunning()){
            /* Start periodic timer */
            timer_start(1000, 1);
        }
        else if(timer_isReadyToGetData()){
            /* Read BME280 data */
            if(SensorBME280_getMeasurementStatus(&bme)){
                SensorBME280_getData(&bme);
                BMENewData = true;
            }

            /*Read wind sensor data*/
            SensorWind_requestSpeed();
            if(SensorWind_speedAvailable()){
                SensorWind_speed(&windSpeed);
                windNewData = true;
            }
        }

        if(BMENewData){
            /* Write data into their attributtes */
            ble_writeTemperatureAttribute(
                bme.sensor_data.temperature - TEMPERATUE_OFFSET);
            ble_writeHumidityAttribute(bme.sensor_data.humidity);
            BMENewData = false;
        }

        if(windNewData){
            /* Write data into their attributtes */
            ble_writeWindSpeedAttribute(windSpeed);
            windNewData = false;
        }
    }
    else{
        /* Stop timer */
        if(timer_isRunning() == true) timer_stop();
    }

    /* Let the CPU go to sleep if the system allows it. */
    sl_power_manager_sleep();
  }
}


