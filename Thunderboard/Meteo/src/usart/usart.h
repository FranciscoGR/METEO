/***************************************************************************//**
 * @file  usart.h
 * @brief USART.
 *******************************************************************************
 *  Created on: 15 may. 2023
 *      Author: Francisco Gonzalez Ruiz
 ******************************************************************************/
#ifndef USART_USART_H_
#define USART_USART_H_

#include <stddef.h>
#include <stdbool.h>

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/
#define USART_BUFLEN              8
#define USART_MODBUS_LEN          8


#define GPIO_PORT_A               0
#define GPIO_PORT_B               1
#define GPIO_PORT_C               2
#define GPIO_PORT_D               3

#define USART_RX_PORT             GPIO_PORT_C
#define USART_RX_PIN              6
#define USART_TX_PORT             GPIO_PORT_C
#define USART_TX_PIN              7
#define USART_TOGGLE_PORT         GPIO_PORT_A
#define USART_TOGGLE_PIN          7

/**************************************************************************//**
 * @brief  usart init function
 *****************************************************************************/
void usart_init(void);

/**************************************************************************//**
 * @brief usart tx data
 * This function transmits data via usart.
 *
 * @param[in] *data Data to transmit
 * @param[in] len   Data len
 *****************************************************************************/
void usart_txData(uint8_t *data, size_t len);

/**************************************************************************//**
 * @brief Returns the sending status
 * This function returns the sending status (enabled or disabled).
 *****************************************************************************/
bool usart_getWindSpeedDataFlag(void);

/**************************************************************************//**
 * @brief Returns wind speed
 * This function returns a wind speed value.
 *****************************************************************************/
uint8_t usart_getWindSpeed(void);

#endif /* USART_USART_H_ */
