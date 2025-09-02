# DFRobot_GP85XX

* [中文版](./README_CN.md)

GP8XXX series driver library on Raspberry Pi (currently compatible with GP8101, GP8101S, GP8211S, GP8413, GP8501, GP8503, GP8512,GP8403,GP8302, GP8600, GP8630N, GP210)

## Product Link([www.dfrobot.com](www.dfrobot.com))

SUK：

1. DFR1034 --- GP8503
2. DFR1035 --- GP8512
3. DFR1036 --- GP8101S
4. DFR1037 --- GP8501
5. DFR1071 --- GP8211S
6. DFR1073 --- GP8413
7. DFR0971 --- GP8403
8. DFR0972 --- GP8302
9. DFR1228 --- GP210  
10. DFR1229 --- GP8600  
11. DFR1230 --- GP8630N  

## Table of Contents

  - [Summary](#summary)
  - [Installation](#installation)
  - [Methods](#methods)
  - [Compatibility](#compatibility)
  - [History](#history)
  - [Credits](#credits)

## Summary
    This library has already provided sample demos for each of the 8 currently compatible products, and users can use them according to their names

## Installation

There two methods: 
1. To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.
2. Search the DFRobot_GP8302 library from the Arduino Software Library Manager and download it.

## Methods

```python

 #################I2C系列#################
  def begin(self)
    '''!
      @brief Initialize the function
      @return returns 0 for success, and other values for failure 
    '''

  def set_dac_outrange(self, range)
    '''!
      @brief Set the DAC output range
      @param range DAC output range
      @n     OUTPUT_RANGE_5V(0-5V)
      @n     OUTPUT_RANGE_6V(0-6V)
      @n     OUTPUT_RANGE_10V(0-10V)
      @n     OUTPUT_RANGE_12V(0-12V)
      @n     OUTPUT_RANGE_10_0V(-10-0V)
      @n     OUTPUT_RANGE_12_0V(-12-0V)
      @n     OUTPUT_RANGE_20MA(0-20mA)
      @n     OUTPUT_RANGE_24MA(0-24mA)
      @return NONE
    '''

  def set_dac_out_voltage(self, data, channel=0)
    '''!
      @brief Set different channel output DAC values
      @param data value corresponding to the data voltage value
      @param channel output channel
      @n 0: Channel 0 (valid when PWM0 output is configured)
      @n 1: Channel 1 (effective when PWM1 output is configured)
      @n 2: All channels (valid when configuring dual channel outputs)
      @return NONE
    '''

  def store(self)
    '''!
      @brief Save the set voltage inside the chip
      @return NONE
    '''


#################PWM系列#################

  def begin(self)
    '''!
      @brief Initialize the function
      @return 0
    '''

  def set_dac_out_voltage(self, data, channel=0)
    '''!
      @brief Set different channel output DAC values
      @param data pwm pulse width
      @param channel output channel
      @n 0: Channel 0 (valid when PWM0 output is configured)
      @n 1: Channel 1 (effective when PWM1 output is configured)
      @n 2: All channels (valid when configuring dual channel outputs)
      @return NONE
    '''

```

## Compatibility

| MCU         | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :--: | :----: | :----: | :--: |
| RaspberryPi2 |      |        |   √    |      |
| RaspberryPi3 |      |        |   √    |      |
| RaspberryPi4 |  √   |        |        |      |

* Python Version

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :--: | :----: | :----: | ---- |
| Python2 |  √   |        |        |      |
| Python3 |  √   |        |        |      |

## History

- 2023/05/10 - Version 1.0.0 released.
- 2025/07/04  - Version 1.0.0 released. add GP8600, GP8630N, GP210
## Credits

- Written by fary( feng.yang@dfrobot.com), 2023. (Welcome to our [website](https://www.dfrobot.com/))
- Written by lr  ( rong.li@dfrobot.com),   2025. (Welcome to our [website](https://www.dfrobot.com/))