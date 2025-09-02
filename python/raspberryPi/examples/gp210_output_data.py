# -*- coding:utf-8 -*-
'''!
  @file  GP210outputData.py
  @brief Output the corresponding current signal through pulse width modulation signal.
  @copyright  Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license  The MIT License (MIT)
  @author  [lr](rong.li@dfrobot.com)
  @version  V1.1
  @date  2025-07-04
  @url  https://github.com/DFRobot/DFRobot_GP8XXX
'''

from __future__ import print_function
import sys
import os
import time

sys.path.append(os.path.dirname(os.path.dirname(os.path.realpath(__file__))))
from DFRobot_GP8XXX import *

# Pass the pin number in BCM encoding
DAC = DFRobot_GP210(pin0=17)

def setup():
  DAC.begin()

  '''
    @brief Set the output DAC value
    @param data PWM duty cycle (0.0-100.0)
    @n The optional parameter (0.0-100.0) corresponds to an output of 0 - 25mA current signal.
  '''
  data=100.0
  DAC.set_dac_out_voltage(data)

def loop():
  pass

if __name__ == "__main__":
  setup()
  while True:
    loop()