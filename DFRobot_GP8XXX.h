/*!
  * @file DFRobot_GP8XXX.h
  * @brief GP8XXX 系列DAC驱动库（目前实现了GP8101,GP8211S,GP8413,GP8501，GP8503，GP8512的驱动办法）
  * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license     The MIT License (MIT)
  * @author      [fary](feng.yang@dfrobot.com)
  * @version  V1.0
  * @date  2023-05-10
  * @url https://github.com/DFRobot/DFRobot_GP8XXX
  */


#ifndef _DFRobot_GP8XXX_H_
#define _DFRobot_GP8XXX_H_

#include "Arduino.h"
#include "Wire.h"

class DFRobot_GP8XXX
{
  public:
    /**
     * @enum eOutPutRange_t
     * @brief Analog voltage output range select
     */
    typedef enum{
      eOutputRange2_5V  = 0,
      eOutputRange5V  = 1,
      eOutputRange10V = 2,
      eOutputRangeVCC   = 3
    }eOutPutRange_t;
    DFRobot_GP8XXX(){

    }

    /**
     * @fn begin
     * @brief 初始化函数
     */
    virtual int begin(void) =0;

    /**
     * @fn setDACOutVoltage
     * @brief 设置不同通道输出DAC值
     * @param data 需要输出的电压值
     * @param channel 输出通道 0:通道0;1:通道1;2:全部通道
     * @param value DAC分辨率 4096 : 12bit ; 32767 : 15bit
     * @return NONE
     */
    virtual void setDACOutVoltage(uint16_t data, uint8_t channel) =0;   
  protected:
    uint16_t _voltage = 0;
};

class DFRobot_GP8XXX_IIC:public DFRobot_GP8XXX
{
  public:

    #define RESOLUTION_12_BIT 0x0FFF
    #define RESOLUTION_15_BIT 0x7FFF
    #define GP8XXX_CONFIG_CURRENT_REG                  uint8_t(0x02)
    #define DFGP8XXX_I2C_DEVICEADDR                    uint8_t(0x58)   //!< i2c address

    #define GP8XXX_STORE_TIMING_HEAD            0x02  ///< Store function timing start head
    #define GP8XXX_STORE_TIMING_ADDR            0x10  ///< The first address for entering store timing
    #define GP8XXX_STORE_TIMING_CMD1            0x03  ///< The command 1 to enter store timing
    #define GP8XXX_STORE_TIMING_CMD2            0x00  ///< The command 2 to enter store timing
    #define GP8XXX_STORE_TIMING_DELAY           10    ///< Store procedure interval delay time: 10ms, more than 7ms
    #define I2C_CYCLE_TOTAL                     5     ///< Total I2C communication cycle
    #define I2C_CYCLE_BEFORE                    1     ///< The first half cycle 2 of the total I2C communication cycle
    #define I2C_CYCLE_AFTER                     2     ///< The second half cycle 3 of the total I2C communication cycle

    /**
     * @brief DFRobot_GP8XXX constructor
     * @param pWire I2C object
     * @param addr I2C address
     */
    DFRobot_GP8XXX_IIC(uint16_t resolution,uint8_t deviceAddr = DFGP8XXX_I2C_DEVICEADDR,TwoWire *pWire = &Wire)
    :_resolution(resolution),_deviceAddr(deviceAddr),_pWire(pWire){

    }

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
	

  protected:
	  /**
     * @fn sendData
     * @brief 设置IIC输入值
     * @param data 需要设置的输入值(0-fff)
     * @param channel 输出通道
     * @n  0:通道0  (配置PWM0输出时有效)
     * @n  1:通道1  (配置PWM1输出时有效)
     * @n  2:全部通道 (配置双通道输出时有效)
     * @return NONE
     */
	  void sendData(uint16_t data, uint8_t channel);

    /**
     * @fn writeRegister
     * @brief Write I2C register
     * @param reg I2C register address
     * @param pBuf Data storage space
     * @param size Read length
     * @return Write result
     * @retval 0 indicates success
     * @retval other values indicate setting failure
     */
    uint8_t writeRegister(uint8_t reg, void* pBuf, size_t size);

    /**
     * @fn startSignal
     * @brief i2c起始信号
     */
    void startSignal(void);

    /**
     * @fn startSignal
     * @brief i2c停止信号
     */	
    void stopSignal(void);

    /**
     * @fn recvAck
     * @brief 接收应答
     * @param ack  要接收的应答信号
     * @return 应答信号
     */	
    uint8_t recvAck(uint8_t ack);

    /**
     * @fn sendByte
     * @brief 软件i2c发送数据
     * @param data 要发送的数据
     * @param ack 应答信号
     * @param bits 发送多少位
     * @param flag 是否接收应答
     * @return 应答信号
     */		
    uint8_t sendByte(uint8_t data, uint8_t ack = 0, uint8_t bits = 8, bool flag = true);
  
  protected:
  
    TwoWire *_pWire;
    int _scl= SCL;
    int _sda = SDA;
    uint16_t _resolution=0;
    uint8_t _deviceAddr;
};

class DFRobot_GP8503: public DFRobot_GP8XXX_IIC
{
  public:
    DFRobot_GP8503(uint16_t resolution = RESOLUTION_12_BIT):DFRobot_GP8XXX_IIC(resolution){};
};

class DFRobot_GP8211S: public DFRobot_GP8XXX_IIC
{
  public:
    DFRobot_GP8211S(uint16_t resolution = RESOLUTION_15_BIT):DFRobot_GP8XXX_IIC(resolution){};
};

class DFRobot_GP8512: public DFRobot_GP8XXX_IIC
{
  public:
    DFRobot_GP8512(uint16_t resolution = RESOLUTION_15_BIT):DFRobot_GP8XXX_IIC(resolution){};
    void setDACOutVoltage(uint16_t voltage, uint8_t channel=0);
};

class DFRobot_GP8413: public DFRobot_GP8XXX_IIC
{
  public:
    DFRobot_GP8413(uint8_t deviceAddr = DFGP8XXX_I2C_DEVICEADDR,uint16_t resolution = RESOLUTION_15_BIT):DFRobot_GP8XXX_IIC(resolution,deviceAddr){};
};

class DFRobot_GP8302: public DFRobot_GP8XXX_IIC
{
  public:
    DFRobot_GP8302(uint8_t deviceAddr = DFGP8XXX_I2C_DEVICEADDR,uint16_t resolution = RESOLUTION_12_BIT):DFRobot_GP8XXX_IIC(resolution,deviceAddr){};
    void setDACOutElectricCurrent(uint16_t current){setDACOutVoltage(current);};
};

class DFRobot_GP8403: public DFRobot_GP8XXX_IIC
{
  public:
    DFRobot_GP8403(uint8_t deviceAddr = DFGP8XXX_I2C_DEVICEADDR,uint16_t resolution = RESOLUTION_12_BIT):DFRobot_GP8XXX_IIC(resolution,deviceAddr){};
};


/**************************************************************************
                       PWM转2路0-2.5V/VCC 模拟电压模块(GP8501)
 **************************************************************************/
class DFRobot_GP8XXX_PWM: public DFRobot_GP8XXX
{
  public:
    DFRobot_GP8XXX_PWM(int pin0 = -1,int pin1 = -1)
    :_pin0(pin0),_pin1(pin1){

    }
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
    
  private:	
	/**
     * @fn sendData
     * @brief 设置PWM占空比
     * @param data pwm 脉宽
     * @param channel 输出通道
     * @n  0:通道0  (配置PWM0输出时有效)
     * @n  1:通道1  (配置PWM1输出时有效)
     * @n  2:全部通道 (配置双通道输出时有效)
     * @return NONE
     */
	void sendData(uint8_t data, uint8_t channel);
  
  protected:

	  int _pin0=-1;
	  int _pin1=-1;
  
};

class DFRobot_GP8501: public DFRobot_GP8XXX_PWM
{
  public:
    DFRobot_GP8501(int pin0 = -1,int pin1 = -1):DFRobot_GP8XXX_PWM(pin0,pin1){};
};

class DFRobot_GP8101: public DFRobot_GP8XXX_PWM
{
  public:
    DFRobot_GP8101(int pin0 = -1):DFRobot_GP8XXX_PWM(pin0){};
};

#endif