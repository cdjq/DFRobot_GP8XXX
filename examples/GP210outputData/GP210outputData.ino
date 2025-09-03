/*!
 * @file GP210outputData.cpp
 * @brief Output the corresponding current signal through pulse width modulation signal .
 * @copyright Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [lr](rong.li@dfrobot.com)
 * @version V1.1.0
 * @date 2025-07-04
 * @url https://github.com/DFRobot/DFRobot_GP8XXX
 */

#include <DFRobot_GP8XXX.h>

//Output the IO port.
#if defined(ESP32) || defined(ESP8266)
  int pwmPin = 13;//IO13
#else
  int pwmPin = 9;
#endif
DFRobot_GP210 GP210(pwmPin);
void setup() {
  double data=255;
  GP210.begin();
  
  /**
   * @brief Set the output DAC value.
   * @param data pwm Pulse width.
   * @n The optional parameter (0-255) corresponds to an output of 0 - 24mA current signal.
   * @n If you are using esp32 or esp8266, you must use a larger range to improve the accuracy.
   * @n The optional parameters (0 - 1023) when using esp32 or esp8266 correspond to a current signal output ranging from 0 to 24 milliamps.
   * @n If you want to output a 4-20mA current signal, please use the following: 
   * @n For example: GP210.setDACOutElectricCurrent(std::max(data, 42.5));
   * @n If you wish to output a 4 - 20 milliampere current signal and are using esp32 or esp8266, please use the following method:
   * @n For example: GP210.setDACOutElectricCurrent(std::max(data*0.84, 170.5));
   */
  GP210.setDACOutElectricCurrent(data);
}

void loop() {

}
