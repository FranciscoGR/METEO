/***************************************************************************//**
 * @file  BME280Config.c
 * @brief BME280 driver config.
 *******************************************************************************
 *  Created on: 14 may. 2023
 *      Author: Francisco Gonzalez Ruiz
 ******************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sl_status.h"
#include "sl_udelay.h"

#include "BME280Config.h"
#include "bme280_defs.h"
#include "i2c.h"

/*******************************************************************************
 *******************************  MACROS   *************************************
 ******************************************************************************/
#define UNUSED(x) (void)(x)

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
static uint8_t dev_addr;

/*******************************************************************************
 ***************************  LOCAL FUNCTIONS   ********************************
 ******************************************************************************/
static BME280_INTF_RET_TYPE BME280Config_i2cRead(uint8_t reg_addr,
                               uint8_t *reg_data, uint32_t len, void *intf_ptr);

static BME280_INTF_RET_TYPE BME280Config_i2cWrite(uint8_t reg_addr,
                                           const uint8_t *reg_data,
                                           uint32_t len, void *intf_ptr);

void BME280Config_delay_us(uint32_t period, void *intf_ptr);

/**************************************************************************//**
 *  @brief Function for reading the sensor's registers through I2C bus.
 *
 *  @param[in] reg_addr  Register address.
 *  @param[out] reg_data Pointer to the data buffer to store the read data.
 *  @param[in] length    No of bytes to read.
 *  @param[in] intf_ptr  Interface pointer
 *****************************************************************************/
static BME280_INTF_RET_TYPE BME280Config_i2cRead(uint8_t reg_addr,
                               uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
  return i2c_read(*(uint8_t*)intf_ptr, &reg_addr, reg_data, len);
}

/**************************************************************************//**
 *  @brief Function for writing the sensor's registers through I2C bus.
 *
 *  @param[in] reg_addr Register address.
 *  @param[in] reg_data Pointer to the data buffer whose value is to be written.
 *  @param[in] length   No of bytes to write.
 *  @param[in] intf_ptr Interface pointer
 *****************************************************************************/
static BME280_INTF_RET_TYPE BME280Config_i2cWrite(uint8_t reg_addr,
                                           const uint8_t *reg_data,
                                           uint32_t len, void *intf_ptr)
{
  /* Prepare data: first position is register to write,
   * rest is data to write*/
  uint8_t data[len];
  memcpy(&data, reg_data, len*sizeof(uint8_t));

  return i2c_write(*(uint8_t*)intf_ptr, &reg_addr, data, len);
}

/**************************************************************************//**
 * @brief Microseconds delay function
 * This function perfoms a delay with microseconds accuracy.
 *
 * @param[in] period     Time interval to delay
 * @param[in] *intf_ptr  Pointer to i2c device address (not used)
 *****************************************************************************/
void BME280Config_delay_us(uint32_t period, void *intf_ptr)
{
  UNUSED(intf_ptr);
  sl_udelay_wait(period);
}

/**************************************************************************//**
 * @brief bme280 sensor instance initialization
 * This function sets the reading and writing functions to read from this
 * sensor, sets the device address an the delay function.
 *
 * @param[in] *bme   Sensor instance
 * @param[in] *intf  Interface to use (i2c or SPI)
 *****************************************************************************/
int8_t BME280Config_interfaceInit(bme280_t *bme, uint8_t intf)
{
  int8_t rslt = BME280_OK;

  if(&(bme->dev) != NULL){
     if(intf == BME280_I2C_INTF){
         dev_addr = BME280_I2C_ADDR_SEC;
         bme->dev.read = BME280Config_i2cRead;
         bme->dev.write = BME280Config_i2cWrite;
         bme->dev.intf = BME280_I2C_INTF;
     }
     else{
         rslt = BME280_E_DEV_NOT_FOUND;
     }

     bme->dev.delay_us = BME280Config_delay_us;
     bme->dev.intf_ptr = &dev_addr;
  }
  else{
     rslt = BME280_E_NULL_PTR;
  }

  return rslt;
}
