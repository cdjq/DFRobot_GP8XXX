# -*- coding:utf-8 -*-
'''!
  @file  gp8512_output_data.py
  @brief 设置输出电压值=，将I2C信号转换为1路0-2.5V或0-VCC(2.7V-5.5V)的模拟电压信号
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
DAC = DFRobot_GP8512(i2c_sda=17,i2c_scl=27)

def setup():

  while DAC.begin()!=0:
    print("与设备通信失败，请检查连接是否正常或者设备地址是否设置正确")
    time.sleep(1)

  '''!
    @brief 设置输出DAC值
    @param data 电压值对应的数据值
    @n （0 - 32767）本模块是15位精度的DAC模块，所以（0 - 32767）分别对应着(0-2.5V)或（0-VCC）,具体对应的电压范围根据模块电压选择波动开关而定
  '''
  DAC.set_dac_out_voltage(32767)

  #将设置的电压保存在芯片内部,掉电保存
  #DAC.store()

def loop():
  pass

if __name__ == "__main__":
  setup()
  while True:
    loop()