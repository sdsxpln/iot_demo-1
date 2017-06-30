
# -*- coding: utf-8 -*-

'说明： '  

import sys, os

from RPi import GPIO
from time import sleep

GPIO.setmode(GPIO.BCM)
GPIO.setup(2, GPIO.OUT)
GPIO.output(2,True)

