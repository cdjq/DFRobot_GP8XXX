# -*- coding:utf-8 -*-
'''!
  @file  gp8101_output_data.py
  @brief 设置输出电压对应的数据值，将PWM信号转换为1路0--5V或0-10V的模拟电压信号
  @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license  The MIT License (MIT)
  @author  [fary](feng.yang@dfrobot.com)
  @version  V1.0
  @date  2023-05-10
  @url  https://github.com/DFRobot/DFRobot_GP8XXX
'''

from __future__ import print_function
import sys
import os
import time

sys.path.append(os.path.dirname(os.path.dirname(os.path.realpath(__file__))))
from DFRobot_GP8XXX import *

# 传入引脚号为BCM编码
DAC = DFRobot_GP8101(pin0=17)

def setup():

  DAC.begin()

  '''!
    @brief 设置输出DAC值
    @param data pwm 占空比（0-100）
    @n （0-100）对应（0-5V）或者（0-10V）,具体对应的电压范围根据模块电压选择波动开关而定
  '''
  DAC.set_dac_out_voltage(100)

def loop():
  pass

if __name__ == "__main__":
  setup()
  while True:
    loop()