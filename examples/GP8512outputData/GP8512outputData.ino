/*!
  * @file GP8512outputData.ino
  * @brief 设置输出电压值，将I2C信号转换为1路0-2.5V或0-VCC(2.7V-5.5V)的模拟电压信号
  * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license     The MIT License (MIT)
  * @author      [fary](feng.yang@dfrobot.com)
  * @version  V1.0
  * @date  2023-05-10
  * @url https://github.com/DFRobot/DFRobot_GP8XXX
  */

#include <DFRobot_GP8XXX.h>

DFRobot_GP8512 GP8512;

void setup() {
  
  
  Serial.begin(9600);

  while(GP8512.begin()!=0){
    Serial.println("与设备通信失败，请检查连接是否正常或者设备地址是否设置正确");
    delay(1000);
  }

  /**
   * @brief 设置输出DAC值
   * @param data 电压值对应的数据值
   * @n （0 - 32767）本模块是15位精度的DAC模块，所以（0 - 32767）分别对应着(0-2.5V)或（0-VCC）,具体对应的电压范围根据模块电压选择波动开关而定
   */
  GP8512.setDACOutVoltage(2000);

  delay(1000);
  //将设置的电压保存在芯片内部,掉电保存
  //GP8512.store();
}

void loop() {
 
}
