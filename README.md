# DFRobot_GP8XXX

* [中文版](./README_CN.md)

GP8XXX 系列在Arduino IDE 上的驱动库（目前已经兼容GP8101,GP8211S,GP8413,GP8501，GP8503，GP8512，GP8403，GP8302）

## Product Link([www.dfrobot.com](www.dfrobot.com))

SUK：

1. DFR1034 --- GP8503
2. DFR1035 --- GP8512
3. DFR1036 --- GP8101
4. DFR1037 --- GP8501
5. DFR1071 --- GP8211S
6. DFR1073 --- GP8413
7. DFR0971 --- GP8403
8. DFR0972 --- GP8302

## Table of Contents

  - [Summary](#summary)
  - [Installation](#installation)
  - [Methods](#methods)
  - [Compatibility](#compatibility)
  - [History](#history)
  - [Credits](#credits)

## Summary

  此库已经争对目前兼容的6款产品分别提供了示例demo,用户可以根据名称进行对应使用

## Installation

There two methods: 
1. To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.
2. Search the DFRobot_GP8XXX library from the Arduino Software Library Manager and download it.

## Methods

```C++

/**************************************************************************
                                  PWM 系列
 **************************************************************************/

	/**
     * @fn begin
     * @brief 初始化函数
     * @return 0
     */
    int begin();

    /**
     * @fn setDACOutVoltage
     * @brief 设置不同通道输出DAC值
     * @param data pwm 脉宽
     * @param channel 输出通道
     * @n  0:通道0  (配置PWM0输出时有效)
     * @n  1:通道1  (配置PWM1输出时有效)
     * @n  2:全部通道 (配置双通道输出时有效)
     * @return NONE
     */
    void setDACOutVoltage(uint16_t data, uint8_t channel=0);

/**************************************************************************
                                  I2C 系列
 **************************************************************************/
    /**
     * @fn begin
     * @brief 初始化函数
     * @return 返回0表示成功，其他值表示失败 
     */
    int begin(void);

    /**
     * @fn setDACOutRange
     * @brief 设置DAC输出范围
     * @param range DAC输出范围
     * @n     eOutputRange0_5V(0-5V)
     * @n     eOutputRange0_10V(0-10V)
     * @return NONE
     */	
    void setDACOutRange(eOutPutRange_t range);

    /**
     * @fn setDACOutVoltage
     * @brief 设置不同通道输出DAC值
     * @param data 电压值对应的数据值
     * @param channel 输出通道
     * @n  0:通道0  (配置PWM0输出时有效)
     * @n  1:通道1  (配置PWM1输出时有效)
     * @n  2:全部通道 (配置双通道输出时有效)
     * @return NONE
     */
    void setDACOutVoltage(uint16_t data, uint8_t channel=0);
	
    /**
     * @fn store
     * @brief 将设置的电压保存在芯片内部
     * @return NONE
     */
    void store(void);

```

## Compatibility

MCU                |  Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno        |       √       |              |             | 
Mega2560           |      √       |              |             | 
Leonardo           |      √       |              |             | 
ESP32              |      √       |              |             | 
ESP8266            |      √       |              |             | 
micro:bit          |      √       |              |             | 
FireBeetle M0      |      √       |              |             | 

## History

- 2023/05/10 - Version 1.0.0 released.

## Credits

- Written by fary( feng.yang@dfrobot.com), 2023. (Welcome to our [website](https://www.dfrobot.com/))