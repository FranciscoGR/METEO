/***************************************************************************//**
 * @file  timer.c
 * @brief Timer.
 *******************************************************************************
 *  Created on: 13 abr. 2023
 *      Author: Francisco Gonzalez Ruiz
 ******************************************************************************/
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "timer.h"

#include "sl_sleeptimer.h"

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
static bool readyToGetData = false;

static sl_sleeptimer_timer_handle_t timerHandle;

/*******************************************************************************
 ***************************  LOCAL FUNCTIONS   ********************************
 ******************************************************************************/
static void timer_cb(sl_sleeptimer_timer_handle_t *handle, void *data);

/**************************************************************************//**
 *  @brief This function configs and starts a timer.
 *
 *  @param[in] time_ms  Timer timeout in milliseconds
 *  @param[in] periodic Indicates if timer will be periodic or oneshot
 *****************************************************************************/
uint32_t timer_start(uint16_t time_ms, uint8_t periodic)
{
  uint32_t status;

  if(periodic == 1){
      status = sl_sleeptimer_start_periodic_timer(&timerHandle,
                                         sl_sleeptimer_ms_to_tick(time_ms),
                                         timer_cb,NULL,3,0);
  }
  else{
      status = sl_sleeptimer_start_timer(&timerHandle,
                                         sl_sleeptimer_ms_to_tick(time_ms),
                                         timer_cb,NULL,3,0);
  }

  return status;
}

/**************************************************************************//**
 *  @brief This function stops a running timer.
 *****************************************************************************/
uint32_t timer_stop()
{
  uint32_t status;

  status = sl_sleeptimer_stop_timer(&timerHandle);

  return status;
}

/**************************************************************************//**
 *  @brief This callback sets the flag that indicates that the timer has
 *  reached the count.
 *
 * @param[in] *handle Sleeptimer handler
 * @param[in] *data   Data
 *****************************************************************************/
static void timer_cb(sl_sleeptimer_timer_handle_t *handle, void *data)
{
  (void)handle;
  (void)data;

  readyToGetData = true;
}

/**************************************************************************//**
 *  @brief This function checks the status of the timer flag, and cleans it
 *  if was set.
 *****************************************************************************/
bool timer_isReadyToGetData()
{
  if(readyToGetData){
      readyToGetData = false;
      return true;
  }

  return false;
}

/***************************************************************************//**
 * @brief Gets the status of a timer.
 * This function returns if the timer is running or not.
 *
 * @param running Pointer to the status of the timer.
 ******************************************************************************/
bool timer_isRunning(void)
{
  bool running;

  sl_sleeptimer_is_timer_running(&timerHandle, &running);

  return running;
}

