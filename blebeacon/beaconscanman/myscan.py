
# -*- coding: utf-8 -*-

'说明： '  

import sys, os
from bluetooth.ble import BeaconService
from bluetooth.ble import GATTRequester



class Reader(object):
    def __init__(self, address):
        self.requester = GATTRequester(address, False)
        self.connect()
        self.name = ""
        self.request_data()

    def connect(self):
        #print("Connecting...", end=' ')
        sys.stdout.flush()

        self.requester.connect(True)
        #print("OK!")

    def request_data(self):
        data = self.requester.read_by_uuid(
                "00002a00-0000-1000-8000-00805f9b34fb")[0]
        try:
            #print("Device name: " + data.decode("utf-8"))
            self.name = data.decode("utf-8")
        except AttributeError:
            #print("Device name: " + data)
            self.name = data




class Beacon(object):
    
    def __init__(self, data, address):
        #print(data)
        self.uuid = data[0]
        self.major = data[1]
        self.minor = data[2]
        self.power = data[3]
        self.rssi = data[4]
        self.address = address
        self.name = "NONAME"
        if( address != "" ):
            try:
                a = Reader(address)
                self.name = a.name
            except Exception:
                pass        

service = BeaconService()
devices = service.scan(6)


for address, data in list(devices.items()):
    b = Beacon(data, address)
    print(b.uuid)
    print(b.address)
    print(b.name)
    print(b.rssi)
    print(b.power)

print("Done.")

