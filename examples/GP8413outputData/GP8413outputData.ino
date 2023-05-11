/*!
  * @file GP8413outputData.ino
  * @brief 设置输出通道、电压值和范围，将I2C信号转换为2路0-5V或0-10V的模拟电压信号。
  * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license     The MIT License (MIT)
  * @author      [Baikunlin](kunlin.bai@dfrobot.com)
  * @version  V1.0
  * @date  2023-02-10
  * @url https://github.com/DFRobot/DFRobot_GP8XXX
  */

#include <DFRobot_GP8XXX.h>
/**************************
----------------------------
| A0 |  A1 | A2 | i2c_addr |
----------------------------
| 0  |  0  | 0  |   0x58   |
----------------------------
| 1  |  0  | 0  |   0x59   |
----------------------------
| 0  |  1  | 0  |   0x5A   |
----------------------------
| 1  |  1  | 0  |   0x5B   |
----------------------------
| 0  |  0  | 1  |   0x5C   |
----------------------------
| 1  |  0  | 1  |   0x5D   |
----------------------------
| 0  |  1  | 1  |   0x5E   |
----------------------------
| 1  |  1  | 1  |   0x5F   |
----------------------------
***************************/
DFRobot_GP8413 GP8413(/*deviceAddr=*/0x58);

void setup() {

  
  Serial.begin(9600);

  while(GP8413.begin()!=0){
    Serial.println("与设备通信失败，请检查连接是否正常或者设备地址是否设置正确");
    delay(1000);
  }

  /**
   * @brief 设置DAC输出范围
   * @param range DAC输出范围
   * @n     eOutputRange5V(0-5V)
   * @n     eOutputRange10V(0-10V)
   */	
  GP8413.setDACOutRange(GP8413.eOutputRange5V);

  /**
   * @brief 设置不同通道输出DAC值
   * @param data 电压值对应的数据值
   * @n （0 - 32767）本模块是15位精度的DAC模块，所以（0 - 32767）分别对应着(0-5V)或（0-10V）,具体对应的电压范围根据模块电压选择波动开关而定
   * @param channel 输出通道
   * @n  0:通道0
   * @n  1:通道1
   * @n  2:全部通道
   */  
  GP8413.setDACOutVoltage(2000,2);

  delay(1000);

  //将设置的电压保存在芯片内部,掉电保存
  //GP8413.store();
}

void loop() {

}
