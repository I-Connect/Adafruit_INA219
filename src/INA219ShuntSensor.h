// INA219ShuntSensor.h
#pragma once

#include "Adafruit_INA219.h"
#include "Arduino.h"
#include "ISenseShuntValued.h"
#include "SenseI2CBusSensor.h"

/*
 * SenseNode implementation for an INA219 Shunt sensorI2C 
 * Address: 0x40
 */
class INA219aShuntSensor : public SenseI2CBusSensor {
public:
  INA219aShuntSensor(uint8_t sensorId);
  ~INA219aShuntSensor();

  void initialize() override;
  float getValueAsFloat() override;
  char* getValueAsChar(char* value, uint8_t size) override;
  byte* getValueInBuffer(byte* buffer) override;
  byte getMinBufferSize() override;
  ShuntValue* getLastValues() { return &lastValues; };

protected:
  void readRawValue() override;

private:
  Adafruit_INA219 ina219;
  ShuntValue lastValues;
};
