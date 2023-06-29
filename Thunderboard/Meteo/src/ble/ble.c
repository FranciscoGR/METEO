/***************************************************************************//**
 * @file  ble.c
 * @brief BLE.
 *******************************************************************************
 *  Created on: 13 abr. 2023
 *      Author: Francisco Gonzalez Ruiz
 ******************************************************************************/
#include "em_common.h"
#include "app_assert.h"
#include "sl_bluetooth.h"
#include "autogen/gatt_db.h"
#include "ble.h"

#include <math.h>

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
/* BLE connection handler*/
static uint8_t BLEConnectionHandle = 0xFF;

/* The advertising set handle allocated from Bluetooth stack. */
static uint8_t BLEAdvertisingSetHandle = 0xff;

/* BLE status*/
static uint8_t BLEStatus;

/* Convert float to byte array to save it in characteristic*/
static size_t ble_floatToByteArray(float num, uint8_t **arr);

/**************************************************************************//**
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;

  switch (SL_BT_MSG_ID(evt->header)) {
    /*
     * This event indicates the device has started and the radio is ready.
     * Do not call any stack command before receiving this boot event!
     */
    case sl_bt_evt_system_boot_id:
      /* Create an advertising set */
      sc = sl_bt_advertiser_create_set(&BLEAdvertisingSetHandle);
      app_assert_status(sc);

      /* Set TX Power to 0 dBm */
      sl_bt_system_set_tx_power(0,0,0,0);

      /* Generate data for advertising */
      sc = sl_bt_legacy_advertiser_generate_data(BLEAdvertisingSetHandle,
                                        sl_bt_advertiser_general_discoverable);
      app_assert_status(sc);

      // Set advertising interval to 100ms.
      sc = sl_bt_advertiser_set_timing(
          BLEAdvertisingSetHandle,
        160, /* min. adv. interval (milliseconds * 1.6) */
        160, /* max. adv. interval (milliseconds * 1.6) */
        0,   /* adv. duration */
        0);  /* max. num. adv. events */
      app_assert_status(sc);

      /* Start advertising and enable connections */
      sc = sl_bt_legacy_advertiser_start(BLEAdvertisingSetHandle,
                                      sl_bt_advertiser_connectable_scannable);
      app_assert_status(sc);

      BLEStatus = BLE_STATUS_ADVERTISING;
      break;

    /*
     * This event indicates that a new connection was opened
     */
    case sl_bt_evt_connection_opened_id:
      BLEConnectionHandle = evt->data.evt_connection_opened.connection;
      BLEStatus = BLE_STATUS_CONNECTED;

      /* Request connection parameter update.
       * conn.interval min 20ms, max 40ms, slave latency 4 intervals,
       * supervision timeout 2 seconds
       * (These should be compliant with Apple Bluetooth Accessory Design
       * Guidelines, both R7 and R8)
       */
      sl_bt_connection_set_parameters(BLEConnectionHandle, 16, 32, 0,
                                      200, 0, 0xFFFF);
      break;

    /*
     * This event indicates that a connection was closed
     */
    case sl_bt_evt_connection_closed_id:
      /* Generate data for advertising */
      sc = sl_bt_legacy_advertiser_generate_data(BLEAdvertisingSetHandle,
                                       sl_bt_advertiser_general_discoverable);
      app_assert_status(sc);

      /* Restart advertising after client has disconnected */
      sc = sl_bt_legacy_advertiser_start(BLEAdvertisingSetHandle,
                                     sl_bt_advertiser_connectable_scannable);
      app_assert_status(sc);
      BLEStatus = BLE_STATUS_ADVERTISING;
      break;

    ///////////////////////////////////////////////////////////////////////////
    // Add additional event handlers here as your application requires!      //
    ///////////////////////////////////////////////////////////////////////////

    /*
     * Default event handler
     */
    default:
      break;
  }
}

/***************************************************************************//**
 * @brief BLE Status getter
 * This function returns the BLE Status
 ******************************************************************************/
uint8_t ble_getStatus(void)
{
  return BLEStatus;
}

/**************************************************************************//**
 * @brief BLE write temperature attribute
 * This function write a temperature value into its BLE attribute.
 *
 * @param[in] temperature Temperature value
 *****************************************************************************/
uint32_t ble_writeTemperatureAttribute(float temperature)
{
  uint32_t ret = 0;

  /* Write gatt attribute value*/
  uint8_t *gatt_temperature;
  size_t size = ble_floatToByteArray(temperature, &gatt_temperature);
  ret = sl_bt_gatt_server_write_attribute_value(gattdb_TEMP, 0,
                                                size,
                                                gatt_temperature);
  free(gatt_temperature);

  return ret;
}

/**************************************************************************//**
 * @brief BLE write humidity attribute
 * This function write a humidity value into its BLE attribute.
 *
 * @param[in] humidity Humidity value
 *****************************************************************************/
uint32_t ble_writeHumidityAttribute(float humidity)
{
  uint32_t ret = 0;

  /* Write gatt attribute value*/
  uint8_t *gatt_humidity;
  size_t size = ble_floatToByteArray(humidity, &gatt_humidity);
  ret = sl_bt_gatt_server_write_attribute_value(gattdb_HUM, 0,
                                                size,
                                                gatt_humidity);
  free(gatt_humidity);

  return ret;
}

/**************************************************************************//**
 * @brief BLE write wind speed attribute
 * This function write a wind speed value into its BLE attribute.
 *
 * @param[in] windSpeed Wind speed value
 *****************************************************************************/
uint32_t ble_writeWindSpeedAttribute(float windSpeed)
{
  uint32_t ret = 0;

  /* Write gatt attribute value*/
  uint8_t *gatt_windSpeed;
  size_t size = ble_floatToByteArray(windSpeed, &gatt_windSpeed);
  ret = sl_bt_gatt_server_write_attribute_value(gattdb_WIND, 0,
                                                size,
                                                gatt_windSpeed);
  free(gatt_windSpeed);

  return ret;
}

/**************************************************************************//**
 * @brief Convert float num to byte array
 * This function converts a float number to a byte array to write it in a
 * BLE attribute.
 *
 * @param[in]  num    Float number
 * @param[out] **arr  Pointer to pointer to destination byte array
 *****************************************************************************/
static size_t ble_floatToByteArray(float num, uint8_t **arr)
{
    uint8_t *num_ptr = (uint8_t *) &num;
    size_t size = sizeof(num);
    *arr = malloc(size);

    for (size_t i = 0; i < size; i++) {
        (*arr)[i] = num_ptr[i];
    }

    return size;
}
