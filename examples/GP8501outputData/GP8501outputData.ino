/*!
  * @file GP8501outputData.ino
  * @brief 设置输出通道、电压值，将PWM信号转换为2路0-2.5V或0-VCC(2.7V-5.5V)的模拟电压信号
  * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license     The MIT License (MIT)
  * @author      [fary](feng.yang@dfrobot.com)
  * @version  V1.0
  * @date  2023-05-10
  * @url https://github.com/DFRobot/DFRobot_GP8XXX
  */

#include <DFRobot_GP8XXX.h>


//#define SINGLE_CHANNEL
#ifdef SINGLE_CHANNEL 
//单通道输出，IO口配置
int pwmPin0 = 9;
DFRobot_GP8501 GP8501(pwmPin0);
#else
//双通道输出，IO口配置
int pwmPin0 = 9;
int pwmPin1 = 10;
DFRobot_GP8501 GP8501(pwmPin0,pwmPin1);
#endif

void setup() {

  GP8501.begin();

  /**
   * @brief 设置不同通道输出DAC值
   * @param data pwm 脉宽
   * @n 可选参数（0-255）对应（0-2.5V）或者（0-VCC）,具体对应的电压范围根据模块电压选择波动开关而定
   * @param channel 输出通道
   * @n  0:通道0  (配置PWM0输出时有效)
   * @n  1:通道1  (配置PWM1输出时有效)
   * @n  2:全部通道 (配置双通道输出时有效)
   */  
  GP8501.setDACOutVoltage(255,2);

}

void loop() {

}
