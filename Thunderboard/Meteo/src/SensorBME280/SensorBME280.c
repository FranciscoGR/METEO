/***************************************************************************//**
 * @file  SensorBME280.c
 * @brief Sensor BME280.
 *******************************************************************************
 *  Created on: 14 may. 2023
 *      Author: Francisco Gonzalez Ruiz
 ******************************************************************************/
#include "SensorBME280.h"
#include "bme280.h"

#include "BME280Config/BME280Config.h"
#include <stdbool.h>
#include "i2c.h"

/**************************************************************************//**
 * @brief Complete bme280 sensor configuration
 * This function inits and configs the bme280 sensor instance.
 *
 * @param[in] *bme Pointer to bme280 sensor instance
 *****************************************************************************/
int8_t SensorBME280_init(bme280_t *bme)
{
  int8_t result = BME280_E_NULL_PTR;

  /* Init I2C peripheral*/
  i2c_init();

  /* Interface preference is updated as a parameter
   * For I2C : BME68X_I2C_INTF
   * For SPI : BME68X_SPI_INTF
   */
  result = BME280Config_interfaceInit(bme, BME280_I2C_INTF);

  /* Initialize sensor*/
  result = bme280_init(&(bme->dev));

  /* Read sensor current settings*/
  result = bme280_get_sensor_settings(&(bme->settings), &(bme->dev));

  /* Configuring the over-sampling rate, filter coefficient and standby time */
  /* Overwrite the desired settings */
  bme->settings.filter = BME280_FILTER_COEFF_2;

  /* Over-sampling rate for humidity, temperature and pressure */
  bme->settings.osr_h = BME280_OVERSAMPLING_1X;
  bme->settings.osr_p = BME280_OVERSAMPLING_1X;
  bme->settings.osr_t = BME280_OVERSAMPLING_1X;

  /* Setting the standby time */
  bme->settings.standby_time = BME280_STANDBY_TIME_0_5_MS;

  /* Set all settings*/
  result = bme280_set_sensor_settings(BME280_SEL_ALL_SETTINGS, &(bme->settings),
                                    &(bme->dev));

  /* Set sensor power mode*/
  result = bme280_set_sensor_mode(BME280_POWERMODE_NORMAL, &(bme->dev));

  /* Calculate measurement time in microseconds*/
  result = bme280_cal_meas_delay(&(bme->period), &(bme->settings));

  return result;
}

/**************************************************************************//**
 * @brief Get measurement status
 * This function returns if there is data available.
 *
 * @param[in] *bme Pointer to bme280 sensor instance
 *****************************************************************************/
bool SensorBME280_getMeasurementStatus(bme280_t *bme)
{
  uint8_t status_reg;

  bme280_get_regs(BME280_REG_STATUS, &status_reg, 1, &(bme->dev));
  if(status_reg & BME280_STATUS_MEAS_DONE){
      return true;
  }

  return false;
}

/**************************************************************************//**
 * @brief Get BME280 sensor data
 * This function saves the sensor readings in the sensor instance.
 *
 * @param[in] *bme Pointer to bme280 sensor instance
 *****************************************************************************/
int8_t SensorBME280_getData(bme280_t *bme)
{
  int8_t result = BME280_E_NULL_PTR;

  /* Read sensor data*/
  bme->dev.delay_us(bme->period, bme->dev.intf_ptr);
  result = bme280_get_sensor_data(BME280_ALL, &(bme->sensor_data), &(bme->dev));

  return result;
}
