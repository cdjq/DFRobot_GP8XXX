/*!
  * @file GP8403outputData.ino
  * @brief 设置输出通道、电压值和范围，将I2C信号转换为2路0-5V或0-10V的模拟电压信号。
  * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license     The MIT License (MIT)
  * @author      [Baikunlin](kunlin.bai@dfrobot.com)
  * @version  V1.0
  * @date  2023-05-24
  * @url https://github.com/DFRobot/DFRobot_GP8XXX
  */

#include <DFRobot_GP8XXX.h>
/**************************
----------------------------
| A2 |  A1 | A0 | i2c_addr |
----------------------------
| 0  |  0  | 0  |   0x58   |
----------------------------
| 0  |  0  | 1  |   0x59   |
----------------------------
| 0  |  1  | 0  |   0x5A   |
----------------------------
| 0  |  1  | 1  |   0x5B   |
----------------------------
| 1  |  0  | 0  |   0x5C   |
----------------------------
| 1  |  0  | 1  |   0x5D   |
----------------------------
| 1  |  1  | 0  |   0x5E   |
----------------------------
| 1  |  1  | 1  |   0x5F   |
----------------------------
***************************/
DFRobot_GP8403 GP8403(/*deviceAddr=*/0x58);

void setup() {

  
  Serial.begin(9600);

  while(GP8403.begin()!=0){
    Serial.println("与设备通信失败，请检查连接是否正常或者设备地址是否设置正确");
    delay(1000);
  }

  /**
   * @brief 设置DAC输出范围
   * @param range DAC输出范围
   * @n     eOutputRange5V(0-5V)
   * @n     eOutputRange10V(0-10V)
   */	
  GP8403.setDACOutRange(GP8403.eOutputRange5V);

  /**
   * @brief 设置不同通道输出DAC值
   * @param data 电压值对应的数据值
   * @n （0 - 4095）本模块是12位精度的DAC模块，所以（0 - 4095）分别对应着(0-5V)或（0-10V）
   * @param channel 输出通道
   * @n  0:通道0
   * @n  1:通道1
   * @n  2:全部通道
   */  
  GP8403.setDACOutVoltage(2000,2);

  delay(1000);

  //将设置的电压保存在芯片内部,掉电保存
  //GP8403.store();
}

void loop() {

}
