
# -*- coding: utf-8 -*-

'说明： '  

import sys, os

from RPi import GPIO
from time import sleep

GPIO.setmode(GPIO.BCM)
GPIO.setup(3, GPIO.OUT)
GPIO.output(3,True)


