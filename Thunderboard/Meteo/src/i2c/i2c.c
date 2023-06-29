/***************************************************************************//**
 * @file  i2c.c
 * @brief i2c interface.
 *******************************************************************************
 *  Created on: 4 ene. 2023
 *      Author: Francisco Gonzalez Ruiz
 ******************************************************************************/
#include "i2c.h"
#include "em_i2c.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "sl_status.h"
#include "sl_udelay.h"

/**************************************************************************//**
 * @brief i2c interface init
 * This function initialize the i2c protocol interface.
 *****************************************************************************/
void i2c_init(void)
{
  int i;
  I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;

  /* Select GPIO peripheral clock */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Select I2C peripheral clock */
  CMU_ClockEnable(cmuClock_I2C0, true);

  /* Output value must be set to 1 to not drive lines low. Set
     SCL first, to ensure it is high before changing SDA. */
  GPIO_PinModeSet(I2C_SCL_PORT, I2C_SCL_PIN, gpioModeWiredAndPullUp, 1);
  GPIO_PinModeSet(I2C_SDA_PORT, I2C_SDA_PIN, gpioModeWiredAndPullUp, 1);

  /* In some situations, after a reset during an I2C transfer, the slave
     device may be left in an unknown state. Send 9 clock pulses to
     set slave in a defined state. */
  for (i = 0; i < 9; i++) {
    GPIO_PinOutClear(I2C_SCL_PORT, I2C_SCL_PIN);
    sl_udelay_wait(SCL_HOLD_TIME_US);
    GPIO_PinOutSet(I2C_SDA_PORT, I2C_SDA_PIN);
    sl_udelay_wait(SCL_HOLD_TIME_US);
  }

  /* Enable pins and set location */
  GPIO->I2CROUTE[0].ROUTEEN = GPIO_I2C_ROUTEEN_SDAPEN | GPIO_I2C_ROUTEEN_SCLPEN;
  GPIO->I2CROUTE[0].SCLROUTE =
      (uint32_t)((I2C_SCL_PIN << _GPIO_I2C_SCLROUTE_PIN_SHIFT) |
                 (I2C_SCL_PORT << _GPIO_I2C_SCLROUTE_PORT_SHIFT));
  GPIO->I2CROUTE[0].SDAROUTE =
      (uint32_t)((I2C_SDA_PIN << _GPIO_I2C_SDAROUTE_PIN_SHIFT) |
                 (I2C_SDA_PORT << _GPIO_I2C_SDAROUTE_PORT_SHIFT));


  /* Set emlib init parameters */
  i2cInit.freq    = I2C_FREQ_STANDARD_MAX;
  i2cInit.clhr    = i2cClockHLRStandard;

  I2C_Init(I2C0, &i2cInit);
}

/**************************************************************************//**
 * @brief i2c reading function
 * This function reads from i2c bus.
 *
 * @param[in] *addr       i2c device address
 * @param[in] *reg        Register to read from
 * @param[in, out] *data  Contains the read data location
 * @param[in] len         Length to read
 *****************************************************************************/
int8_t i2c_read(uint8_t addr , uint8_t *reg, uint8_t *data, uint32_t len)
{
  I2C_TransferSeq_TypeDef    seq;
  I2C_TransferReturn_TypeDef ret;

  /* Set address and mode*/
  seq.addr  = addr << 1;
  seq.flags = I2C_FLAG_WRITE_READ;

  /* Select command to issue */
  seq.buf[0].data   = reg;
  seq.buf[0].len    = 1;

  /* Select location/length of data to be read */
  seq.buf[1].data = data;
  seq.buf[1].len  = (uint16_t)len;

  uint32_t timeout = TRANSFER_TIMEOUT;

  /* Do a polled transfer */
  ret = I2C_TransferInit(I2C0, &seq);
  while (ret == i2cTransferInProgress && timeout--){
    ret = I2C_Transfer(I2C0);
  }

  if (ret != i2cTransferDone) {
    return SL_STATUS_TRANSMIT;
  }

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * @brief i2c writing function
 * This function writes on i2c bus.
 *
 * @param[in] *addr  i2c device address
 * @param[in] *reg   Register to write in
 * @param[in] *data  Contains the data to write
 * @param[in] len    Length to write
 *****************************************************************************/
int8_t i2c_write(uint8_t addr, uint8_t *reg, uint8_t *data, uint32_t len)
{
  I2C_TransferSeq_TypeDef    seq;
  I2C_TransferReturn_TypeDef ret;

  /* Set address and mode*/
  seq.addr  = addr << 1;
  seq.flags = I2C_FLAG_WRITE_WRITE;

  /* Select command to issue */
  seq.buf[0].data   = reg;
  seq.buf[0].len    = 1;

  /* Select location/length of data to be read */
  seq.buf[1].data = data;
  seq.buf[1].len  = (uint16_t)len;

  uint32_t timeout = TRANSFER_TIMEOUT;

  /* Do a polled transfer */
  ret = I2C_TransferInit(I2C0, &seq);
  while (ret == i2cTransferInProgress && timeout--){
    ret = I2C_Transfer(I2C0);
  }

  if (ret != i2cTransferDone) {
    return SL_STATUS_TRANSMIT;
  }

  return SL_STATUS_OK;
}
