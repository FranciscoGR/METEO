/***************************************************************************//**
 * @file  i2c.h
 * @brief i2c interface.
 *******************************************************************************
 *  Created on: 4 ene. 2023
 *      Author: Francisco Gonzalez Ruiz
 ******************************************************************************/
#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/
#define I2C_SCL_PORT            gpioPortC
#define I2C_SCL_PIN             1
#define I2C_SDA_PORT            gpioPortC
#define I2C_SDA_PIN             2
#define SCL_HOLD_TIME_US        100
#define TRANSFER_TIMEOUT        300000

/**************************************************************************//**
 * @brief i2c interface init
 * This function initialize the i2c protocol interface.
 *****************************************************************************/
void i2c_init(void);

/**************************************************************************//**
 * @brief i2c reading function
 * This function reads from i2c bus.
 *
 * @param[in] *addr       i2c device address
 * @param[in] *reg        Register to read from
 * @param[in, out] *data  Contains the read data location
 * @param[in] len         Length to read
 *****************************************************************************/
int8_t i2c_read(uint8_t addr , uint8_t *reg, uint8_t *data, uint32_t len);

/**************************************************************************//**
 * @brief i2c writing function
 * This function writes on i2c bus.
 *
 * @param[in] *addr  i2c device address
 * @param[in] *reg   Register to write in
 * @param[in] *data  Contains the data to write
 * @param[in] len    Length to write
 *****************************************************************************/
int8_t i2c_write(uint8_t addr, uint8_t *reg, uint8_t *data, uint32_t len);

#endif /* I2C_H_ */
