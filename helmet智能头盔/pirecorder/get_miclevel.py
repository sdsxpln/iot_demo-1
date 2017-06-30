
# -*- coding: utf-8 -*-

'说明： '  

import sys, os

from RPi import GPIO
from time import sleep

GPIO.setmode(GPIO.BCM)
GPIO.setup(17, GPIO.IN)

with open('get_miclevel_status', 'w') as f:
    f.write( str(GPIO.input(17)) )
    


