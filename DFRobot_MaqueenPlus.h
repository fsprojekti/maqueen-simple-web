/*!
 * @file DFRobot_MaqueenPlus.h
 * @brief This is a library for MaqueenPlus from DFRobot
 * @details This library can be used to control the corresponding sensors on MaqueenPlus to complete different projects and functions
 * @copyright    Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence      The MIT License (MIT)
 * @author       [TangJie](jie.tang@dfrobot.com)
 * @version      V1.0.1
 * @eGDAte       2020-09-15
 * @url          https://github.com/DFRobot/DFRobot_MaqueenPlus
 */

#ifndef  DFRobot_MaqueenPlus_H
#define  DFRobot_MaqueenPlus_H

#include <Arduino.h>
#include <Wire.h>

#define ENABLE_DBG
#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define DFROBOT_MAQUEEMPLUS_IRPIN    16
#define DFROBOT_MAQUEEMPLUS_LEFT     1
#define DFROBOT_MAQUEEMPLUS_RIGHT    2
#define DFROBOT_MAQUEEMPLUS_L1       1
#define DFROBOT_MAQUEEMPLUS_L2       2
#define DFROBOT_MAQUEEMPLUS_M       5
#define DFROBOT_MAQUEEMPLUS_R1       3
#define DFROBOT_MAQUEEMPLUS_R2       4
#define DFROBOT_MAQUEEMPLUS_S1       1
#define DFROBOT_MAQUEEMPLUS_S2       2

class DFRobot_MaqueenPlus
{
public:
 /**
  * @struct ePID
  * @brief Enable or disable PID
  */
  typedef enum {
    eOFF = 0,
    eON  = 1
  }ePID;

 /**
  * @enum ePosition
  * @brief Positionition selection, suitable for RGB LEDs and motor selection
  */
  typedef enum {
    eLEFT  = 1,
    eRIGHT = 2,
    eALL   = 3
  }ePosition;

 /**
  * @enum eDir
  * @brief Motor direction selection
  */
  typedef enum {
    eCW  = 1,
    eCCW = 2
  }eDir;

 /**
  * @enum ePatrol
  * @brief line-tracking sensor selection
  */
  typedef enum {
    eL1 = 1,
    eL2 = 2,
    eL3 = 5,
    eR1 = 3,
    eR2 = 4,
    eR3 = 6
  }ePatrol;

 /**
  * @enum eColor
  * @brief RGB LEDs color selection
  */
  typedef enum {
    eRED    = 1,
    eGREEN  = 2,
    eBLUE   = 4,
    eYELLOW = 3,
    ePINK   = 5,
    eCYAN   = 6,
    eWHITE  = 7,
    ePUT    = 8
  }eColor;

 /**
  * @enum eServo
  * @brief Serve port selection
  */
  typedef enum {
    eS1 = 1,
    eS2 = 2,
    eS3 = 3
  }eServo;

 /**
  * @enum ePin
  * @brief Ultrasonic pin selection
  */
  typedef enum {
    eP0  = 0,
    eP1  = 1,
    eP2  = 2,
    eP8  = 8,
    eP12 = 12,
    eP13 = 13,
    eP14 = 14,
    eP15 = 15
  }ePin;

  /**
   * @fn DFRobot_MaqueenPlus
   * @brief Constructor
   * @param pWire  I2C object
   * @param address I2C address
   * @param pSDA pin number for SDA (default: 22)
   * @param pSCL pin number for SCL (default: 21)
   * @return None 
   */
  DFRobot_MaqueenPlus(TwoWire *pWire = &Wire, uint8_t address = 0x10, uint8_t pSDA = 21, uint8_t pSCL = 22)
  {
    _pWire = pWire;
    _address = address;
	_pSDA = pSDA;
	_pSCL = pSCL;
  };
  
  // Overloaded constructor only for pSDA and pSCL
  DFRobot_MaqueenPlus(uint8_t pSDA, uint8_t pSCL)
  {
    _pWire = &Wire;
    _address = 0x10;
    _pSDA = pSDA;
    _pSCL = pSCL;
  };

 /**
  * @fn begin
  * @brief Init I2C until success 
  * @return uint8_t type, indicate returning init status
  * @retval 0 Init succeeded
  * @retval -1 Init failed
  */
  uint8_t begin(void);

 /**
  * @fn PIDSwitch
  * @brief PID operation control
  * @param state To disable or enable PID
  * @return None
  */
  void PIDSwitch(ePID state);

 /**
  * @fn motorControl
  * @brief Control the direction and speed of MaqueenPlus
  * @param motor Motor control selection
  * @param direction Motor rotation direction 
  * @param speed Motor speed(range:0~255)
  * @return None
  */
  void motorControl(ePosition motor, eDir direction, uint8_t speed);

 /**
  * @fn getSpeed
  * @brief Get wheel speed
  * @param motor Select left or right motor
  * @return Return the speed of the selected motor 
  */
  uint8_t getSpeed(ePosition motor);

 /**
  * @fn getDirection
  * @brief Get rotation direction
  * @param motor Select left or right motor 
  * @return  0: stop 1: forward 2: backward
  */
  uint8_t getDirection(ePosition motor);

 /**
  * @fn getDistance
  * @brief  Get the number of revolutions
  * @param motor Select left or right motor
  * @return Return the revolutions
  */
  float getDistance(ePosition motor);

 /**
  * @fn clearDistance
  * @brief Clear the number of revolutions
  * @param motor Select left or right motor
  * @return None
  */
  void clearDistance(ePosition motor);

 /**
  * @fn getPatrol
  * @brief  Get line-tracking sensor status
  * @param senser Select line-tracking sensor 
  * @return Returns the status of line-tracking sensor
  */
  uint8_t getPatrol(ePatrol senser);

 /**
  * @fn getGrayscale
  * @brief Get grayscale value of line-tracking sensor
  * @param senser Select line-tracking sensor 
  * @return  Return the grayscale value of line-tracking sensor
  */
  uint16_t getGrayscale(ePatrol sensor);

  /**
    * @fn getGrayscale
    * @brief Get grayscale value of line-tracking sensors
    * @param senser Select line-tracking sensor
    * @return  Return the grayscale value of line-tracking sensors
    */
   uint16_t* getGrayscale();

 /**
  * @fn setRGB
  * @brief Set the RGB led color
  * @param colour Select Color
  * @return None
  */
  void setRGB(ePosition light,eColor color);

 /**
  * @fn servoControl
  * @brief Servo control
  * @param servo Select servo
  * @param angle Control servo angle(range:0°~180°)
  * @return None
  */
  void servoControl(eServo servo, uint8_t angle);

 /**
  * @fn ultraSonic
  * @brief Get ultrasonic distance
  * @param trig   TRIG Pin
  * @param echo   ECHO Pin
  * @return  Return ultrasonic distance information
  */
  uint8_t ultraSonic(ePin trig, ePin echo);

 /**
  * @fn getIR
  * @brief Get infrared data
  * @return  Return infrared key information
  */
 uint32_t getIR(void);

 /**
  * @fn getVersion
  * @brief  Get version information
  * @return  Return version information
  */
  String getVersion(void);

private:
  uint8_t _echoPin;
  uint8_t _trlgPin;
  TwoWire *_pWire;
  uint8_t _address;
  uint16_t _pulseWidth = 0;
  uint16_t _irCode = 0x00;
  uint32_t _duration;
  uint8_t _pSDA = 21;
  uint8_t _pSCL = 22;
 /**
  * @fn myPulseIn
  * @brief  Get level change time
  */
  uint64_t myPulseIn(uint32_t pin, uint32_t value, long maxDuration = 100000);

 /**
  * @fn writeReg
  * @brief   Write register value through IIC bus
  * @param reg  Register address 8bits
  * @param pBuf Storage cache to write data in
  * @param size The length of data to be written
  */
  void writeReg(uint8_t reg, void *pBuf, size_t size);
  
 /**
  * @fn readReg
  * @brief Read register value through IIC bus
  * @param reg  Register address 8bits
  * @param pBuf Read data storage cache
  * @param size Read the length of data
  * @return Return the read length, 0 indicates it failed to read 
  */
  uint8_t readReg(uint8_t reg, void *pBuf, size_t size);

};
#endif
