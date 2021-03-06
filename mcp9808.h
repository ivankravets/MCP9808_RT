#pragma once
//
//    FILE: mcp9808.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino Library for I2C mcp9808 temperature sensor
//    DATE: 2020-05-03
//     URL: https://github.com/RobTillaart/MCP9808_RT
//

#include "Arduino.h"
#include "Wire.h"

// VALID ADDRESSES, max 8 sensors on one bus
// 0x24 .. 0x31

// config register masks,
// check the datasheet for exact usage
#define MCP9808_THYSTERESIS     0x0600
#define MCP9808_SHUTDOWN        0x0100
#define MCP9808_CRIT_LOCK       0x0080
#define MCP9808_WIN_LOCK        0x0040
#define MCP9808_INT_CLEAR       0x0020
#define MCP9808_ALERT_STATUS    0x0010
#define MCP9808_ALERT_CTRL      0x0008
#define MCP9808_ALERT_SELECT    0x0004
#define MCP9808_ALERT_POLAR     0x0002
#define MCP9808_ALERT_MODE      0x0001


class MCP9808
{
public:
#if defined(ESP8266) || defined(ESP32)
  // dataPin and clockPin can be used for ESP8266
  MCP9808(const uint8_t addr, const uint8_t dataPin = 255, const uint8_t clockPin = 255);
#endif
  // ctor for UNO
  MCP9808(const uint8_t addr);

  void setAddress(const uint8_t address, TwoWire *wire);

  // could become separate functions in later release
  // ==> 20 getters and setters! big footprint
  // separate 
  void      setConfigRegister(uint16_t cfg);
  uint16_t  getConfigRegister();

  void      setTupper(float f);
  float     getTupper();
  void      setTlower(float f);
  float     getTlower();
  void      setTcritical(float f);
  float     getTcritical();

  void      setAlertPin(uint8_t pin);
  bool      hasAlert();

  float     getTemperature();
  uint8_t   getStatus();

  void      setResolution(uint8_t res);
  uint8_t   getResolution();

  uint16_t  getManufacturerID();
  uint8_t   getDeviceID();
  uint8_t   getRevision();


private:
  uint8_t   _status = 0;   // enum
  uint8_t   _alertPin;
  uint8_t   _address;
  TwoWire*  _wire;

  
  void      writeFloat(uint8_t reg, float f);
  float     readFloat(uint8_t reg);
  void      writeReg8(uint8_t reg, uint8_t value);
  uint8_t   readReg8(uint8_t reg);
  void      writeReg16(uint8_t reg, uint16_t value);
  uint16_t  readReg16(uint8_t reg);
};

// -- END OF FILE --
