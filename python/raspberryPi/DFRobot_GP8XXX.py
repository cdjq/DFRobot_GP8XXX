from __future__ import print_function
import time
import datetime
import RPi.GPIO as GPIO
from abc import ABC, abstractmethod

class DFRobot_GP8XXX(ABC):
  ##Select DAC output voltage of 0-2.5V
  OUTPUT_RANGE_2_5V = 0
  ##Select DAC output voltage of 0-5V
  OUTPUT_RANGE_5V = 1
  ##Select DAC output voltage of 0-10V
  OUTPUT_RANGE_10V = 2
  ##Select DAC output voltage of 0-VCC
  OUTPUT_RANGE_VCC = 3
  def __init__(self):
    '''!
      @brief Module init
    '''
    pass
  def begin(self):
    pass
  
  def set_dac_out_voltage(self,voltage,channel):
    pass

class DFRobot_GP8XXX_IIC(DFRobot_GP8XXX):
  RESOLUTION_12_BIT =0x0FFF
  RESOLUTION_15_BIT =0x7FFF
  GP8XXX_CONFIG_CURRENT_REG           = 0x02
  ## i2c address
  GP8XXX_I2C_DEVICE_ADDR              = 0x58
  ## Store function timing start head        
  GP8XXX_STORE_TIMING_HEAD            = 0x02
  ## The first address for entering store timing        
  GP8XXX_STORE_TIMING_ADDR            = 0x10 
  ## The command 1 to enter store timing    
  GP8XXX_STORE_TIMING_CMD1            = 0x03
  ## The command 2 to enter store timing  
  GP8XXX_STORE_TIMING_CMD2            = 0x00  
  ## Store procedure interval delay time: 10ms, more than 7ms
  GP8XXX_STORE_TIMING_DELAY           = 0.01
  ## Total I2C communication cycle   
  I2C_CYCLE_TOTAL                     = 0.000005   
  ## The first half cycle 2 of the total I2C communication cycle  
  I2C_CYCLE_BEFORE                    = 0.000001     
  ## The second half cycle 3 of the total I2C communication cycle
  I2C_CYCLE_AFTER                     = 0.000002     
 
  def __init__(self,sda,scl,resolution,device_addr=GP8XXX_I2C_DEVICE_ADDR):
    '''!
      @fn __init__
      @brief i2c类初始化
      @param sda i2c数据引脚
      @param scl i2c时钟引脚
      @param resolution 分辨率
      @param device_addr i2c设备地址 
    '''
    self._resolution = resolution
    self._device_addr = device_addr
    self._scl = scl
    self._sda = sda

  def begin(self):
    '''!
      @fn begin
      @brief 初始化函数
      @param 初始化函数
      @return 返回0表示成功，其他值表示失败 
    '''
    GPIO.setwarnings(False)  # 屏蔽警告
    GPIO.setmode(GPIO.BCM)  # 设置引脚模式BCM
    GPIO.setup(self._scl, GPIO.OUT)
    GPIO.setup(self._sda, GPIO.OUT)
    self._start_signal()
    ret = self._send_byte(self._device_addr << 1, 1)
    self._stop_signal()
    return ret

  def set_dac_outrange(self, range):
    '''!
      @fn set_dac_outrange
      @brief 设置DAC输出范围
      @param range DAC输出范围
      @n     eOutputRange0_5V(0-5V)
      @n     eOutputRange0_10V(0-10V)
      @return NONE
    '''
    if range == self.OUTPUT_RANGE_5V :
      list =[0x00]
      self._write_reg(self.GP8XXX_CONFIG_CURRENT_REG>>1,list,1)
    elif range == self.OUTPUT_RANGE_10V :
      list = [0x11]
      self._write_reg(self.GP8XXX_CONFIG_CURRENT_REG>>1,list,1)

  def set_dac_out_voltage(self, data, channel=0):
    '''!
      @fn set_dac_out_voltage
      @brief 设置不同通道输出DAC值
      @param data 电压值对应的数据值
      @param channel 输出通道
      @n  0:通道0  (配置PWM0输出时有效)
      @n  1:通道1  (配置PWM1输出时有效)
      @n  2:全部通道 (配置双通道输出时有效)
      @return NONE
    '''
    if data > self._resolution :
      data = self._resolution
    if self._resolution == self.RESOLUTION_12_BIT:
      data = data << 4
    elif self._resolution == self.RESOLUTION_15_BIT:
      data = data << 4
    self._send_data(data, channel)

  def store(self):
    '''!
      @fn store
      @brief 将设置的电压保存在芯片内部
      @return NONE
    '''
    self._start_signal()
    self._send_byte(self.GP8XXX_STORE_TIMING_HEAD, 0, 3, False)
    self._stop_signal()
    self._start_signal()
    self._send_byte(self.GP8XXX_STORE_TIMING_ADDR)
    self._send_byte(self.GP8XXX_STORE_TIMING_CMD1)
    self._stop_signal()

    self._start_signal()
    self._send_byte(self._device_addr << 1, 1)
    self._send_byte(self.GP8XXX_STORE_TIMING_CMD2, 1)
    self._send_byte(self.GP8XXX_STORE_TIMING_CMD2, 1)
    self._send_byte(self.GP8XXX_STORE_TIMING_CMD2, 1)
    self._send_byte(self.GP8XXX_STORE_TIMING_CMD2, 1)
    self._send_byte(self.GP8XXX_STORE_TIMING_CMD2, 1)
    self._send_byte(self.GP8XXX_STORE_TIMING_CMD2, 1)
    self._send_byte(self.GP8XXX_STORE_TIMING_CMD2, 1)
    self._send_byte(self.GP8XXX_STORE_TIMING_CMD2, 1)
    self._stop_signal()

    time.sleep(self.GP8XXX_STORE_TIMING_DELAY)

    self._start_signal()
    self._send_byte(self.GP8XXX_STORE_TIMING_HEAD, 0, 3, False)
    self._stop_signal()
    self._start_signal()
    self._send_byte(self.GP8XXX_STORE_TIMING_ADDR)
    self._send_byte(self.GP8XXX_STORE_TIMING_CMD2)
    self._stop_signal()

  def _send_data(self, data, channel):
    '''!
      @fn _send_data
      @brief 设置IIC输入值
      @param data 需要设置的输入值(0-fff)
      @param channel 输出通道
      @n  0:通道0  (配置PWM0输出时有效)
      @n  1:通道1  (配置PWM1输出时有效)
      @n  2:全部通道 (配置双通道输出时有效)
      @return NONE
    '''
    buf = [data & 0xff,(data >> 8 ) & 0xff ,data & 0xff,(data >> 8 ) & 0xff]
    if channel == 0 :
      self._write_reg(self.GP8XXX_CONFIG_CURRENT_REG, buf,2)
    elif channel == 1 :
      self._write_reg(self.GP8XXX_CONFIG_CURRENT_REG << 1, buf,2)
    elif channel == 2 :
      self._write_reg(self.GP8XXX_CONFIG_CURRENT_REG , buf,4)

  def _write_reg(self, reg, data,size):
    '''!
      @fn _write_reg
      @brief 向设备寄存器中写入值
      @param reg 寄存器地址
      @param data 要写入的数据
      @param size 数据长度
    '''
    self._start_signal()
    self._send_byte(self._device_addr << 1, 1)
    self._send_byte(reg, 1)
    for i in range(0,size):
      self._send_byte(data[i], 1)
    self._stop_signal()

  def _start_signal(self):
    '''!
      @fn _start_signal
      @brief i2c起始信号
    '''
    GPIO.output(self._scl, GPIO.HIGH)
    GPIO.output(self._sda, GPIO.HIGH)
    time.sleep(self.I2C_CYCLE_BEFORE)
    GPIO.output(self._sda, GPIO.LOW)
    time.sleep(self.I2C_CYCLE_AFTER)
    GPIO.output(self._scl, GPIO.LOW)
    time.sleep(self.I2C_CYCLE_TOTAL)

  def _stop_signal(self):
    '''!
      @fn _stop_signal
      @brief i2c停止信号
    '''
    GPIO.output(self._sda, GPIO.LOW)
    time.sleep(self.I2C_CYCLE_BEFORE)
    GPIO.output(self._scl, GPIO.HIGH)
    time.sleep(self.I2C_CYCLE_TOTAL)
    GPIO.output(self._sda, GPIO.HIGH)
    time.sleep(self.I2C_CYCLE_TOTAL)

  def _recv_ack(self, ack=0):
    '''!
      @fn _recv_ack
      @brief 接收应答
      @param ack  要接收的应答信号
      @return 应答信号
    '''
    ack_ = 0
    error_time = 0
    GPIO.setup(self._sda, GPIO.IN)
    time.sleep(self.I2C_CYCLE_BEFORE)
    GPIO.output(self._scl, GPIO.HIGH)
    time.sleep(self.I2C_CYCLE_AFTER)
    while GPIO.input(self._sda) != ack:
      time.sleep(0.000001)
      error_time += 1
      if error_time > 250:
        break
    ack_ = GPIO.input(self._sda)
    time.sleep(self.I2C_CYCLE_BEFORE)
    GPIO.output(self._scl, GPIO.LOW)
    time.sleep(self.I2C_CYCLE_AFTER)
    GPIO.setup(self._sda, GPIO.OUT)
    return ack_

  def _send_byte(self, data, ack=0, bits=8, flag=True):
    '''!
      @fn _send_byte
      @brief 软件i2c发送数据
      @param data 要发送的数据
      @param ack 应答信号
      @param bits 发送多少位
      @param flag 是否接收应答
      @return 应答信号
    '''
    i = bits
    data = data & 0xFF
    while i > 0:
      i -= 1
      if data & (1 << i):
        GPIO.output(self._sda, GPIO.HIGH)
      else:
        GPIO.output(self._sda, GPIO.LOW)
      time.sleep(self.I2C_CYCLE_BEFORE)
      GPIO.output(self._scl, GPIO.HIGH)
      time.sleep(self.I2C_CYCLE_TOTAL)
      GPIO.output(self._scl, GPIO.LOW)
      time.sleep(self.I2C_CYCLE_AFTER)
    if flag:
      return self._recv_ack(ack)
    else:
      GPIO.output(self._sda, GPIO.LOW)
      GPIO.output(self._scl, GPIO.HIGH)
    return ack


class DFRobot_GP8503(DFRobot_GP8XXX_IIC):
  def __init__(self,i2c_sda,i2c_scl):
    return super().__init__(sda=i2c_sda,scl=i2c_scl,resolution=self.RESOLUTION_12_BIT)

class DFRobot_GP8211S(DFRobot_GP8XXX_IIC):
  def __init__(self,i2c_sda,i2c_scl):
    return super().__init__(sda=i2c_sda,scl=i2c_scl,resolution=self.RESOLUTION_15_BIT)

class DFRobot_GP8512(DFRobot_GP8XXX_IIC):
  def __init__(self,i2c_sda,i2c_scl):
    return super().__init__(sda=i2c_sda,scl=i2c_scl,resolution=self.RESOLUTION_15_BIT)

class DFRobot_GP8413(DFRobot_GP8XXX_IIC):
  def __init__(self,i2c_sda,i2c_scl,i2c_addr=0x58):
    return super().__init__(sda=i2c_sda,scl=i2c_scl,resolution=self.RESOLUTION_15_BIT,device_addr=i2c_addr)

class DFRobot_GP8XXX_PWM(DFRobot_GP8XXX):

  def __init__(self,pin0=-1,pin1=-1):
    '''!
      @fn __init__
      @brief pwm类初始化
      @param pin0 pwm 0号通道对应的引脚 
      @param pin1 pwm 1号通道对应的引脚 
    '''
    self._pin0 = pin0
    self._pin1 = pin1

  def begin(self):
    '''!
      @fn begin
      @brief 初始化函数
      @return 0
    '''
    GPIO.setwarnings(False)  # 屏蔽警告
    GPIO.setmode(GPIO.BCM)  # 设置引脚模式BCM
    if self._pin0 != -1 :
      GPIO.setup(self._pin0, GPIO.OUT)  # 设置引脚R0方向输出
      self._PWM0 = GPIO.PWM(self._pin0, 100)
      self._PWM0.start(0)
    if self._pin1 != -1 :
      GPIO.setup(self._pin1, GPIO.OUT)  # 设置引脚R1方向输出
      self._PWM1 = GPIO.PWM(self._pin1,100)
      self._PWM1.start(0)

  def set_dac_out_voltage(self, data, channel=0):
    '''!
      @fn set_dac_out_voltage
      @brief 设置不同通道输出DAC值
      @param data pwm 脉宽
      @param channel 输出通道
      @n  0:通道0  (配置PWM0输出时有效)
      @n  1:通道1  (配置PWM1输出时有效)
      @n  2:全部通道 (配置双通道输出时有效)
      @return NONE
    '''
    if data > 100:
      data = 100
    if data < 0:
      data = 0
    if (channel == 0) and (self._pin0 != -1) :
      self._PWM0.ChangeDutyCycle(data)
    elif (channel == 1) and (self._pin1 != -1) :
      self._PWM1.ChangeDutyCycle(data)
    elif (channel == 2) and (self._pin0 != -1) and (self._pin1 != -1) :
      self._PWM0.ChangeDutyCycle(data)
      self._PWM1.ChangeDutyCycle(data)

class DFRobot_GP8501(DFRobot_GP8XXX_PWM):
  def __init__(self,pin0=-1,pin1=-1):
    return super().__init__(pin0,pin1)

class DFRobot_GP8101(DFRobot_GP8XXX_PWM):
  def __init__(self,pin0=-1):
    return super().__init__(pin0,-1)