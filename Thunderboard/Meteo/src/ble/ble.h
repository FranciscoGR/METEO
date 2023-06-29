/***************************************************************************//**
 * @file  ble.h
 * @brief BLE.
 *******************************************************************************
 *  Created on: 13 abr. 2023
 *      Author: Francisco Gonzalez Ruiz
 ******************************************************************************/

#ifndef BLE_BLE_H_
#define BLE_BLE_H_

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/
#define BLE_STATUS_ADVERTISING    1      /* Advertising state (default)*/
#define BLE_STATUS_CONNECTED      2      /* Connected state*/

/***************************************************************************//**
 * @brief BLE Status getter
 * This function returns the BLE Status.
 ******************************************************************************/
uint8_t ble_getStatus(void);

/**************************************************************************//**
 * @brief BLE write temperature attribute
 * This function write a temperature value into its BLE attribute.
 *
 * @param[in] temperature Temperature value
 *****************************************************************************/
uint32_t ble_writeTemperatureAttribute(float temperature);

/**************************************************************************//**
 * @brief BLE write humidity attribute
 * This function write a humidity value into its BLE attribute.
 *
 * @param[in] humidity Humidity value
 *****************************************************************************/
uint32_t ble_writeHumidityAttribute(float humidity);

/**************************************************************************//**
 * @brief BLE write wind speed attribute
 * This function write a wind speed value into its BLE attribute.
 *
 * @param[in] windSpeed Wind speed value
 *****************************************************************************/
uint32_t ble_writeWindSpeedAttribute(float windSpeed);
#endif /* BLE_BLE_H_ */
