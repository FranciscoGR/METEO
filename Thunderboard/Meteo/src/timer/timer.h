/***************************************************************************//**
 * @file  timer.c
 * @brief Timer.
 *******************************************************************************
 *  Created on: 13 abr. 2023
 *      Author: Francisco Gonzalez Ruiz
 ******************************************************************************/
#ifndef TIMER_TIMER_H_
#define TIMER_TIMER_H_

#include <stdbool.h>

/**************************************************************************//**
 *  @brief This function configs and starts a timer.
 *
 *  @param[in] time_ms  Timer timeout in milliseconds
 *  @param[in] periodic Indicates if timer will be periodic or oneshot
 *****************************************************************************/
uint32_t timer_start(uint16_t time_ms, uint8_t periodic);

/**************************************************************************//**
 *  @brief This function stops a running timer.
 *****************************************************************************/
uint32_t timer_stop();

/**************************************************************************//**
 *  @brief This function checks the status of the timer flag, and cleans it
 *  if was set.
 *****************************************************************************/
bool timer_isReadyToGetData();

/***************************************************************************//**
 * @brief Gets the status of a timer.
 * This function returns if the timer is running or not.
 *
 * @param running Pointer to the status of the timer.
 ******************************************************************************/
bool timer_isRunning(void);

#endif /* TIMER_TIMER_H_ */
