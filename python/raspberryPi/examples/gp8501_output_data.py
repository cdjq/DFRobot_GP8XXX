# -*- coding:utf-8 -*-
'''!
  @file  gp8501_output_data.py
  @brief 设置输出通道、电压值，将PWM信号转换为2路0-2.5V或0-VCC(2.7V-5.5V)的模拟电压信号
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
#传入引脚号采用的是BCM编码
DAC = DFRobot_GP8501(pin0=17,pin1=18)

def setup():

  DAC.begin()

  '''!
    @brief 设置不同通道输出DAC值
    @param data pwm 占空比 （0-100）
    @n 可选参数（0-100）对应（0-2.5V）或者（0-VCC）,具体对应的电压范围根据模块电压选择波动开关而定
    @param channel 输出通道 0:通道0;1:通道1;2:全部通道
  '''
  DAC.set_dac_out_voltage(100, 2)

def loop():
  pass

if __name__ == "__main__":
  setup()
  while True:
    loop()