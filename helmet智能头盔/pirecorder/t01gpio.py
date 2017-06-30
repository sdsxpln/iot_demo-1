
# -*- coding: utf-8 -*-

'说明： '  

import sys, os

from RPi import GPIO
from time import sleep

GPIO.setmode(GPIO.BCM)
GPIO.setup(2, GPIO.OUT)
GPIO.setup(3, GPIO.OUT)
GPIO.setup(4, GPIO.IN)
GPIO.setup(17, GPIO.IN)
while True:
    GPIO.output(2,True)
    GPIO.output(3,True)
    print( GPIO.input(4), end=" " )
    print( GPIO.input(17) )
    sys.stdout.flush()
    sleep(0.31)
    GPIO.output(2,False)
    GPIO.output(3,False)
    sleep(0.31)
    
    
    


