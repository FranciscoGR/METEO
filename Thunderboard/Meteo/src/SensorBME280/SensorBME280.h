/***************************************************************************//**
 * @file  SensorBME280.h
 * @brief Sensor BME280.
 *******************************************************************************
 *  Created on: 14 may. 2023
 *      Author: Francisco Gonzalez Ruiz
 ******************************************************************************/
#ifndef SENSORBME280_SENSORBME280_H_
#define SENSORBME280_SENSORBME280_H_

#include <stdbool.h>
#include "BME280Config/BME280Config.h"

/**************************************************************************//**
 * @brief Complete bme280 sensor configuration
 * This function inits and configs the bme280 sensor instance.
 *
 * @param[in] *bme Pointer to bme280 sensor instance
 *****************************************************************************/
int8_t SensorBME280_init(bme280_t *bme);

/**************************************************************************//**
 * @brief Get measurement status
 * This function returns if there is data available.
 *
 * @param[in] *bme Pointer to bme280 sensor instance
 *****************************************************************************/
bool SensorBME280_getMeasurementStatus(bme280_t *bme);

/**************************************************************************//**
 * @brief Get BME280 sensor data
 * This function saves the sensor readings in the sensor instance.
 *
 * @param[in] *bme Pointer to bme280 sensor instance
 *****************************************************************************/
int8_t SensorBME280_getData(bme280_t *bme);

#endif /* SENSORBME280_SENSORBME280_H_ */
