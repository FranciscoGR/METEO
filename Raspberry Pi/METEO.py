# Libraries
import sys
import time
from SensorBME680 import BME680
from SQLiteManager import SQLiteManager
from BLEManager import BLEManager

# Macros
BME680_I2C_ADDR            = 0x77
BLE_EXTERNAL_DEVICE_NAME   = "METEO"
SQLITE_DB_NAME             = "values.db"

# Main 
if __name__ == '__main__':
    try:        
        # Initial message 
        print("\n METEO - Domestic Inside/Outside Environmental Monitor")

        # Start sqlite
        mySQLite = SQLiteManager()
        mySQLite.create_connection(SQLITE_DB_NAME)
        mySQLite.create_default_tables()
        mySQLite.close_connection()

        # Init Bluetooth manager
        blemanager = BLEManager(BLE_EXTERNAL_DEVICE_NAME)
        BLEConnection = False
        
        # Init BME680 sensor
        SensorBME680 = BME680(BME680_I2C_ADDR)
        #SensorBME680.burnInSensor()

        # Read counter
        count = 59

        # Infinite loop
        while True:
            # BLE connection
            if blemanager.getConnectionStatus() == False:
                blemanager.scanAndConnect()

            # Special case: read AQ every second to keep resistance plate hot
            AQ = SensorBME680.getAirQuality()

            # Read sensor data every minute
            if count == 59:
                # Open database connection
                mySQLite.create_connection(SQLITE_DB_NAME)

                # Read inside sensor values
                temperatureIN = SensorBME680.getTemperature()
                humidityIN    = SensorBME680.getRelativeHumidity()
                pressure      = SensorBME680.getPressure()
                altitude      = SensorBME680.getAltitude()
                HI           = SensorBME680.getHI()
                print('--> INSIDE VALUES: {0:.2f} C,{1:.3f} %RH, {2:.3f}hPa, {3:.3f} M, {4:.3f} %, {5:.3f} C'.format(temperatureIN,humidityIN,pressure,altitude, AQ, HI))
                mySQLite.insert_invalues(temperatureIN,humidityIN,pressure,altitude,AQ,HI)   

                # Read outside sensor values
                if blemanager.getConnectionStatus() == True:
                    temperatureOUT = blemanager.getTemperature()
                    humidityOUT = blemanager.getHumidity()
                    windSpeed = blemanager.getWindSpeed()
                    print('--> OUTSIDE VALUES: {0:.2f} C,{1:.3f} %RH, {2:.3f} m/s'.format(temperatureOUT,humidityOUT,windSpeed))
                    mySQLite.insert_outvalues(temperatureOUT,humidityOUT,windSpeed) 
                
                # Close database connection
                mySQLite.close_connection()

                # Reset count
                count = 0

            else:
                # Increment count
                count += 1

            # Sleep 1 second
            time.sleep(1)  

    except KeyboardInterrupt:
        print("\n Exiting...")
        blemanager.disconnect()
        mySQLite.close_connection()
        sys.exit(0)