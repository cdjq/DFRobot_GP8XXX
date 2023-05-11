/*!
  * @file GP8101outputData.ino
  * @brief 设置输出电压值，将PWM信号转换为1路0--5V或0-10V的模拟电压信号
  * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license     The MIT License (MIT)
  * @author      [fary](feng.yang@dfrobot.com)
  * @version  V1.0
  * @date  2023-05-10
  * @url https://github.com/DFRobot/DFRobot_GP8XXX
  */

#include <DFRobot_GP8XXX.h>

//输出IO口
int pwmPin = 9;
DFRobot_GP8101 GP8101(pwmPin);
void setup() {

  GP8101.begin();
  
  /**
   * @brief 设置输出DAC值
   * @param data pwm 脉宽
   * @n 可选参数（0-255）对应（0-5V）或者（0-10V）,具体对应的电压范围根据模块电压选择波动开关而定
   */
  GP8101.setDACOutVoltage(255);
}

void loop() {

}
