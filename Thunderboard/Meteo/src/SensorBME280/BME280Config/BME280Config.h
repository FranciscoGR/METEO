/***************************************************************************//**
 * @file  BME280Config.h
 * @brief BME280 driver config.
 *******************************************************************************
 *  Created on: 14 may. 2023
 *      Author: Francisco Gonzalez Ruiz
 ******************************************************************************/
#ifndef SENSORBME280_BME280CONFIG_BME280CONFIG_H_
#define SENSORBME280_BME280CONFIG_BME280CONFIG_H_

#include "bme280_defs.h"

/*******************************************************************************
 ***********************  ESTRUCTURES DECLARATION   ****************************
 ******************************************************************************/
typedef struct bme280
{
  uint32_t period;
  struct bme280_dev dev;
  struct bme280_settings settings;
  struct bme280_data sensor_data;
}bme280_t;

/**************************************************************************//**
 * @brief bme280 sensor instance initialization
 * This function sets the reading and writing functions to read from this
 * sensor, sets the device address an the delay function.
 *
 * @param[in] *bme   Sensor instance
 * @param[in] *intf  Interface to use (i2c or SPI)
 *****************************************************************************/
int8_t BME280Config_interfaceInit(bme280_t *bme, uint8_t intf);

#endif /* SENSORBME280_BME280CONFIG_BME280CONFIG_H_ */
