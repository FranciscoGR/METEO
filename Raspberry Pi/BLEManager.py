from bluepy.btle import Scanner, DefaultDelegate, Peripheral, UUID
import struct

# Scan delegate class
class ScanDelegate(DefaultDelegate):
    def __init__(self):
        DefaultDelegate.__init__(self)

    def handleDiscovery(self, dev, isNewDev, isNewData):
        if isNewDev:
            pass
        elif isNewData:
            pass

# BLE handle class
class BLEManager():
    def __init__(self,device_name):
        # Device name 
        self.device_name = device_name
        self.device_addr = None

        # Connection status
        self.connectionStatus = False

        # Service and characteristics UUID
        self.meteo_uuid       = "085bb4e6-c55a-49db-a818-7d93960821c8" 
        self.temperature_uuid = "3f85803e-e824-4b4c-9080-0ac047c4524f"
        self.humidity_uuid    = "172ae52e-99ce-46c2-a16f-4c508231f7e6"
        self.windSpeed_uuid   = "369c95fb-5bde-4d35-b8f1-43f993ef3c66"

        # BLE Scanner delegate
        self.scanner = Scanner().withDelegate(ScanDelegate())
        self.peripheral = None
        self.services = None
    
    # Scan and connect function
    def scanAndConnect(self):
        try:
            # Scan for devices
            devices = self.scanner.scan(1.0)
            for dev in devices:
                for (adtype, desc, value) in dev.getScanData():
                    if desc == "Complete Local Name" and value == self.device_name:
                        self.device_addr = dev.addr
                        print("Device found...")

            if(self.device_addr):
                # Connect to device
                print("Connecting to device...")
                self.peripheral = Peripheral(self.device_addr)
                print("Connected!")

                # Get BLE services
                print("Getting BLE services...")
                self.services = self.peripheral.getServices()
                
                # Set connection status
                self.connectionStatus = True

                return True
            
            else:
                print("Device not found...")
                return False
        except Exception as e:
            print(e)
            return False
        
    # Disconnect function
    def disconnect(self):
        if self.connectionStatus == True:
            self.device_addr = None
            self.peripheral.disconnect()

    # Characteristic reading function
    def _readCharacteristic(self, service_uuid, characteristic_uuid):
        service = self.peripheral.getServiceByUUID(service_uuid)
        characteristic = service.getCharacteristics(UUID(characteristic_uuid))[0]
        return characteristic.read()

    # Get Temperature function
    def getTemperature(self):
        try:
            value = bytes(self._readCharacteristic(self.meteo_uuid, self.temperature_uuid))
            return struct.unpack('<f', value)[0]
        except Exception as e:
            print(e)

            # Set connection status
            self.disconnect()
            self.connectionStatus = False

            return 0.0
        
     # Get Humidity function   
    def getHumidity(self):
        try:
            value = bytes(self._readCharacteristic(self.meteo_uuid, self.humidity_uuid))
            return struct.unpack('<f', value)[0]
        except Exception as e:
            print(e)

            # Set connection status
            self.disconnect()
            self.connectionStatus = False

            return 0.0
    
    # Get Wind speed function
    def getWindSpeed(self):
        try:
            value = bytes(self._readCharacteristic(self.meteo_uuid, self.windSpeed_uuid))
            return struct.unpack('<f', value)[0]
        except Exception as e:
            print(e)

            # Set connection status
            self.disconnect()
            self.connectionStatus = False

            return 0.0

    # Get connection status function    
    def getConnectionStatus(self):
        return self.connectionStatus