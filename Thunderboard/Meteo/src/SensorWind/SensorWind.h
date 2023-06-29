/***************************************************************************//**
 * @file  SensorWind.h
 * @brief Sensor Wind.
 *******************************************************************************
 *  Created on: 30 may. 2023
 *      Author: Francisco Gonzalez Ruiz
 ******************************************************************************/

#ifndef SENSORWIND_SENSORWIND_H_
#define SENSORWIND_SENSORWIND_H_

#include <stdbool.h>

/**************************************************************************//**
 * @brief Inits wind speed sensor
 * This function inits the usart peripheral to get wind speed values.
 *****************************************************************************/
void SensorWind_init(void);

/**************************************************************************//**
 * @brief Get speed available
 * This function returns if there is an available wind speed.
 *****************************************************************************/
bool SensorWind_speedAvailable(void);

/**************************************************************************//**
 * @brief Request wind speed
 * This function requests for a wind speed value.
 *****************************************************************************/
void SensorWind_requestSpeed(void);

/**************************************************************************//**
 * @brief Get wind speed
 * This function returns a wind speed value.
 *
 * @param[in] *speed Pointer to wind speed variable
 *****************************************************************************/
void SensorWind_speed(float *speed);

#endif /* SENSORWIND_SENSORWIND_H_ */
