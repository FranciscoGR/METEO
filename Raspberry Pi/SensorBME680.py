import adafruit_bme680
import board
import time

# BME680 handle class
class BME680():
    def __init__(self, i2c_address):

        # BME680 Sensor instance
        self.sensor = adafruit_bme680.Adafruit_BME680_I2C(i2c=board.I2C(), address=i2c_address)
        
        # Local sea-level pressure
        self.sensor.sea_level_pressure = 1016.0

        # Gas lower and upper limits
        self.gas_lower_limit = 0
        self.gas_upper_limit = 0

        # Humidity ideal value and max and min values
        self.humidity_ideal_value = 40.0
        self.humidity_max_value = 80.0
        self.humidity_min_value = 20.0 

        # Temperature ideal value, max and min values and sensor offset
        self.temperature_ideal_value = 22.0 
        self.temperature_max_value = 30.0
        self.temperature_min_value = 16.0
        self.temperature_offset = 5.0

        # Air Quality weights
        self.iaq_gas_weight = 0.75
        self.iaq_humidity_weight = 0.25

        # Rothfusz thermal confort coefficients
        self.c1 = -8.78469475556
        self.c2 = 1.61139411
        self.c3 = 2.33854883889
        self.c4 = -0.14611605
        self.c5 = -0.012308094
        self.c6 = -0.0164248277778
        self.c7 = 2.211732 * (10**-3)
        self.c8 = 7.2546 * (10**-4)
        self.c9 = -3.582 * (10**-6)
    
    # Burn-in sensor's gas resistance plate function
    def burnInSensor(self):
        start_time = time.time()
        curr_time = time.time()
        burn_in_time = 300
        burn_in_data = []
        print('Burning in gas sensor for 5 minutes... ')

        while curr_time - start_time < burn_in_time:
            curr_time = time.time()
            gas = self.sensor.gas
            burn_in_data.append(gas)
            time.sleep(1)

        self.gas_upper_limit = sum(burn_in_data[-50:]) / 50.0
        print('Gas reference fixed in: ', self.gas_upper_limit)
    
    # Get Temperature function
    def getTemperature(self):
        return self.sensor.temperature - self.temperature_offset
    
    # Get Relative Humidity function
    def getRelativeHumidity(self):
        return self.sensor.humidity
    
    # Get Pressure function
    def getPressure(self):
        return self.sensor.pressure
    
    # Get Altitude function
    def getAltitude(self):
        return self.sensor.altitude
    
    # Gas score calculation function for AQ
    def _gasScore(self, gas_resistance):
        if gas_resistance < self.gas_lower_limit:
            return 0
        elif gas_resistance > self.gas_upper_limit:
            return 100.0 * self.iaq_gas_weight
        else:
            return self.iaq_gas_weight * 100.0 * gas_resistance / (self.gas_upper_limit - self.gas_lower_limit)
    
    # Humidity score calculation function for AQ
    def _humidityScore(self, relativeHumidity):
        if relativeHumidity > (self.humidity_ideal_value - 5.0) and \
           relativeHumidity < (self.humidity_ideal_value + 5.0):
            return self.iaq_humidity_weight * 100.0
        else:
            if relativeHumidity < (self.humidity_ideal_value - 5.0):
                if relativeHumidity < self.humidity_min_value:
                    return 0
                else:
                    return self.iaq_humidity_weight * 100.0 * (
                        (relativeHumidity - self.humidity_min_value) / 
                        (self.humidity_ideal_value - self.humidity_min_value))
            else:
                if relativeHumidity > self.humidity_max_value:
                    return 0
                else:
                    return self.iaq_humidity_weight * 100.0 * (
                        (self.humidity_max_value - relativeHumidity) / 
                        (self.humidity_max_value - self.humidity_ideal_value))

    # Get AQ function
    def getAirQuality(self):
        gas_score = self._gasScore(self.sensor.gas)
        humidity_score = self._humidityScore(self.sensor.humidity)

        return gas_score + humidity_score
    
    # Get Heat Index function
    def getHI(self):
        t = self.sensor.temperature - self.temperature_offset
        rh = self.sensor.humidity
        HI = (self.c1 + self.c2*t + self.c3*rh + self.c4*t*rh + self.c5*(t**2) + 
               self.c6*(rh**2) + self.c7*(t**2)*rh + self.c8*t*(rh**2) + self.c9*(t**2)*(rh**2))
        return HI
       