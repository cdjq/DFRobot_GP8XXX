/*!
  * @file GP8302outputData.ino
  * @brief 设置输出电流值，将I2C信号转换为1路4-20mA模拟电流输出。
  * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license     The MIT License (MIT)
  * @author      [fary](feng.yang@dfrobot.com)
  * @version  V1.0
  * @date  2023-05-24
  * @url https://github.com/DFRobot/DFRobot_GP8XXX
  */

#include <DFRobot_GP8XXX.h>

DFRobot_GP8302 GP8302;

void setup() {
  
  Serial.begin(9600);

  while(GP8302.begin()!=0){
    Serial.println("与设备通信失败，请检查连接是否正常或者设备地址是否设置正确");
    delay(1000);
  }

  /**
   * @brief 设置不同通道输出DAC值
   * @param data 电压值对应的数据值
   * @n （0 - 4095）本模块是12位精度的DAC模块，所以（0 - 4095）分别对应着(0-25mA)
   * @param channel 输出通道
   * @n  0:通道0
   * @n  1:通道1
   * @n  2:全部通道
   */   
  GP8302.setDACOutElectricCurrent(2048);

  delay(1000);
  
  //将设置的电压保存在芯片内部,掉电保存
  //GP8302.store();
}

void loop() {

}
