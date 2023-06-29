/***************************************************************************//**
 * @file  usart.c
 * @brief USART.
 *******************************************************************************
 *  Created on: 15 may. 2023
 *      Author: Francisco Gonzalez Ruiz
 ******************************************************************************/
#include "em_cmu.h"
#include "em_usart.h"
#include "em_gpio.h"
#include "sl_udelay.h"

#include "usart.h"

#include <stddef.h>
#include <string.h>
#include <stdbool.h>

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
/* RX buffer*/
static uint8_t rxbuff[USART_BUFLEN - 1];

/* RX character position in RX buffer*/
static uint8_t inpos = 0;

/* Sensor data sending status (activated or deactivated)*/
static bool windSpeedAvailable = false;

/* Modbus Address received flag*/
static bool modbusAddressReceived = false;

/* Modbus Function received flag*/
static bool modbusFunctionReceived = false;

/* Modbus Address value*/
static uint8_t modbusAddress = 0x01;

/* Modbus Function value*/
static uint8_t modbusFunction = 0x03;

/* Modbus command to ask for wind speed*/
uint8_t modbusGetWindSpeed[] = {0x01,0x03,0x00,0x16,0x00,0x01,0x65,0xCE};

/* Local variable to store windSpeed when received*/
static uint8_t windSpeed = 0;

/**************************************************************************//**
 * @brief  usart init function
 *****************************************************************************/
void usart_init(void)
{
  /* Enable clock to USART0*/
  CMU_ClockEnable(cmuClock_USART0, true);

  /* Configure the USART TX pin as an output and USART RX pin as an input*/
  GPIO_PinModeSet(USART_TX_PORT, USART_TX_PIN, gpioModePushPull, 0);
  GPIO_PinModeSet(USART_RX_PORT, USART_RX_PIN, gpioModeInput, 0);
  GPIO_PinModeSet(USART_TOGGLE_PORT, USART_TOGGLE_PIN, gpioModePushPull, 1);

  /* Route USART0 TX and RX to the board controller TX and RX pins*/
  GPIO->USARTROUTE[0].TXROUTE =
            (USART_TX_PORT << _GPIO_USART_TXROUTE_PORT_SHIFT)
            | (USART_TX_PIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
  GPIO->USARTROUTE[0].RXROUTE =
            (USART_RX_PORT << _GPIO_USART_RXROUTE_PORT_SHIFT)
            | (USART_RX_PIN << _GPIO_USART_RXROUTE_PIN_SHIFT);

  /* Enable RX and TX signals now that they have been routed*/
  GPIO->USARTROUTE[0].ROUTEEN = GPIO_USART_ROUTEEN_RXPEN
                                | GPIO_USART_ROUTEEN_TXPEN;


  /* Default asynchronous initializer (115.2 Kbps, 8N1, no flow control)*/
  USART_InitAsync_TypeDef init = USART_INITASYNC_DEFAULT;
  init.baudrate = 9600;

  /* Configure and enable USART0*/
  USART_InitAsync(USART0, &init);

  /* Enable NVIC USART sources*/
  NVIC_ClearPendingIRQ(USART0_RX_IRQn);
  NVIC_EnableIRQ(USART0_RX_IRQn);

  /* Enable receive data valid interrupt*/
  USART_IntEnable(USART0, USART_IEN_RXDATAV);
}

/**************************************************************************//**
 * @brief usart tx data
 * This function transmits data via usart.
 *
 * @param[in] *data Data to transmit
 * @param[in] len   Data len
 *****************************************************************************/
void usart_txData(uint8_t *data, size_t len)
{
  size_t i;
  for(i=0; i<len; i++){
      USART_Tx(USART0, data[i]);
  }
}

/**************************************************************************//**
 * @brief The USART0 receive interrupt saves incoming characters.
 *****************************************************************************/
void USART0_RX_IRQHandler(void)
{
  /* Get the character just received*/
  uint32_t aux;
  aux = USART0->RXDATA;

  if(!modbusAddressReceived){
      if(aux == modbusAddress){
          modbusAddressReceived = true;
          rxbuff[inpos] = aux;
          inpos++;
      }
  }else if(!modbusFunctionReceived){
      if(modbusAddressReceived && (aux == modbusFunction)){
          modbusFunctionReceived = true;
          rxbuff[inpos] = aux;
          inpos++;
      }
      else{
          modbusAddressReceived = false;
          inpos = 0;
      }
  }
  else{
      rxbuff[inpos] = aux;

      if (inpos < USART_BUFLEN - 1){
        inpos++;
      }
      else{
        modbusAddressReceived = false;
        modbusFunctionReceived = false;
        inpos = 0;

        windSpeed = rxbuff[4];
        windSpeedAvailable = true;
      }
  }
}

/**************************************************************************//**
 * @brief Returns if there is an available speed
 * This function returns if there is a wind speed value available.
 *****************************************************************************/
bool usart_getWindSpeedDataFlag(void)
{
  if(windSpeedAvailable){
      windSpeedAvailable = false;
      return true;
  }
  return false;
}

/**************************************************************************//**
 * @brief Returns wind speed
 * This function returns a wind speed value.
 *****************************************************************************/
uint8_t usart_getWindSpeed(void)
{
  return windSpeed;
}
