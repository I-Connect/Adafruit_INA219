// INA219ShuntSensor.h
#pragma once

#include "arduino.h"
#include <string>
#include "SenseI2CBusSensor.h"
#include "ISenseShuntValued.h"
#include "Adafruit_INA219.h"


/*
  I2C address: 0x40
*/
class INA219aShuntSensor : public SenseI2CBusSensor
{
public:
  INA219aShuntSensor(uint8_t sensorId);
  ~INA219aShuntSensor();

  void initialize() override;
  float getValueAsFloat() override;
  char* getValueAsChars(char* value) override;
  byte* getValueInBuffer(byte* buffer) override;
  byte getMinBufferSize() override;
  ShuntValue* getLastValues() { return &lastValues; };

protected:
  void readRawValue() override;

private:
  Adafruit_INA219 ina219;
  ShuntValue lastValues;
};

