/*!
  * @file GP8211SoutputData.ino
  * @brief 设置输出通道、电压值，将I2C信号转换为1路0-10V的模拟电压信号。
  * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license     The MIT License (MIT)
  * @author      [fary](feng.yang@dfrobot.com)
  * @version  V1.0
  * @date  2023-05-10
  * @url https://github.com/DFRobot/DFRobot_GP8XXX
  */

#include <DFRobot_GP8XXX.h>

DFRobot_GP8211S GP8211S;

void setup() {

  Serial.begin(9600);

  while(GP8211S.begin()!=0){
    Serial.println("与设备通信失败，请检查连接是否正常或者设备地址是否设置正确");
    delay(1000);
  }
 
  /**
   * @brief 设置DAC输出范围
   * @param range DAC输出范围
   * @n     eOutputRange5V(0-5V)
   * @n     eOutputRange10V(0-10V)
   */	
  GP8211S.setDACOutRange(GP8211S.eOutputRange5V);
 
  /**
   * @brief 设置不同通道输出DAC值
   * @param data 电压值对应的数据值
   * @n （0 - 32767）本模块是15位精度的DAC模块，所以（0 - 32767）分别对应着（0-10V）
   */   
  GP8211S.setDACOutVoltage(32767);

  delay(1000);

  //将设置的电压保存在芯片内部,掉电保存
  //GP8211S.store();
}

void loop() {

}
