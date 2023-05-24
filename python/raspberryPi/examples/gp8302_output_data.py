# -*- coding:utf-8 -*-
'''!
  @file  gp8302_output_data.py
  @brief 设置输出电流值，将I2C信号转换为1路4-20mA模拟电流输出。
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
# 本示例采用软件I2C驱动，不建议传入硬件I2C对应的引脚接口，传入引脚号采用的是BCM编码
DAC = DFRobot_GP8302(i2c_sda=17,i2c_scl=27)

def setup():

  while DAC.begin()!=0:
    print("与设备通信失败，请检查连接是否正常或者设备地址是否设置正确")
    time.sleep(1)

  '''!
    @brief 设置不同通道输出DAC值
    @param data 电流值对应的数据值
    @n （0 - 4095）本模块是12位精度的DAC模块，所以（0 - 4095）分别对应着(0-25mA)
    @param channel 输出通道
    @n  0:通道0
    @n  1:通道1
    @n  2:全部通道
  '''
  DAC.set_dac_out_electric_current(4095)

  #将设置的电流保存在芯片内部,掉电保存
  #DAC.store()

def loop():
  pass

if __name__ == "__main__":
  setup()
  while True:
    loop()