#!/usr/bin/env python
# test BLE Scanning software
# koki 15072015

import time
import blescan
import sys
import json

import bluetooth._bluetooth as bluez
from beacon import Beacon

dev_id = 0
try:
	sock = bluez.hci_open_dev(dev_id)
	print "ble thread started"

except:
	print "error accessing bluetooth device..."
	sys.exit(1)

blescan.hci_le_set_scan_parameters(sock)
blescan.hci_enable_le_scan(sock)




while True:
	returnedList = blescan.parse_events(sock, 10)
	allbs = {}
	for beac in returnedList:
		uuid = beac['uuid']
		if not uuid.startswith('0613ff4c'):
			allbs[uuid] = beac

#        print('found beacons:')
        for bs_key in sorted(allbs.keys()):
            if allbs[bs_key]['mac'] in ['fa:03:70:67:58:34', '1ff:21:01:f4:61:32']:
                bs = allbs[bs_key]
                print('mac: {}, rssi: {}, minor: {}, txp: {}\n'.format(bs['mac'], bs['rssi'], bs['minor'], bs['txp']))
	with open('/home/ritksm/iBeacon-Scanner-for-RPi/beacons.json','w') as of:
		json.dump(allbs,of)
        #time.sleep(2)
