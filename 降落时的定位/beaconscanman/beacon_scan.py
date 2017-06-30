# -*- coding: utf-8 -*-

from bluetooth.ble import BeaconService

"""
https://github.com/karulis/pybluez/blob/master/examples/ble/beacon_scan.py
"""

class Beacon(object):
    
    def __init__(self, data, address):
        print(data)
        self._uuid = data[0]
        self._major = data[1]
        self._minor = data[2]
        self._power = data[3]
        self._rssi = data[4]
        self._address = address
        
    def __str__(self):
        ret = "Beacon: address:{ADDR} uuid:{UUID} major:{MAJOR}"\
                " minor:{MINOR} txpower:{POWER} rssi:{RSSI}"\
                .format(ADDR=self._address, UUID=self._uuid, MAJOR=self._major,
                        MINOR=self._minor, POWER=self._power, RSSI=self._rssi)
        return ret

service = BeaconService()
devices = service.scan(2)

for address, data in list(devices.items()):
    b = Beacon(data, address)
    print(b)

print("Done.")
