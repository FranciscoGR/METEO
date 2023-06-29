/***************************************************************************//**
 * @file  SensorWind.c
 * @brief Sensor Wind.
 *******************************************************************************
 *  Created on: 30 may. 2023
 *      Author: Francisco Gonzalez Ruiz
 ******************************************************************************/
#include "em_gpio.h"
#include "sl_udelay.h"

#include "SensorWind.h"
#include "usart.h"

#include <stdbool.h>

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
/* Speed request modbus command*/
static uint8_t modbus_windSpeedRequest[] =
    {0x01,0x03,0x00,0x16,0x00,0x01,0x65,0xCE};


/**************************************************************************//**
 * @brief Inits wind speed sensor
 * This function inits the usart peripheral to get wind speed values.
 *****************************************************************************/
void SensorWind_init(void)
{
  /* Init USART peripheral*/
  usart_init();
}

/**************************************************************************//**
 * @brief Get speed available
 * This function returns if there is an available wind speed.
 *****************************************************************************/
bool SensorWind_speedAvailable(void)
{
  return usart_getWindSpeedDataFlag();
}

/**************************************************************************//**
 * @brief Request wind speed
 * This function requests for a wind speed value.
 *****************************************************************************/
void SensorWind_requestSpeed(void)
{
  /* Enable MAX485 sending mode*/
  GPIO_PinOutSet(USART_TOGGLE_PORT,USART_TOGGLE_PIN);

  /* Send modbus request to anemometer*/
  usart_txData(modbus_windSpeedRequest, 8);
  sl_udelay_wait(2000);

  /* Enable MAX485 receiving mode*/
  GPIO_PinOutClear(USART_TOGGLE_PORT, USART_TOGGLE_PIN);
}

/**************************************************************************//**
 * @brief Get wind speed
 * This function returns a wind speed value.
 *
 * @param[in] *speed Pointer to wind speed variable
 *****************************************************************************/
void SensorWind_speed(float *speed)
{
  *speed = (float)usart_getWindSpeed()/10.0;
}
