// INA219ShuntSensor.h
#pragma once

#include "Adafruit_INA219.h"
#include "Arduino.h"
#include "ISenseShuntValued.h"
#include "I2CBusSensor.h"
#include "ObservableNode.h"

/*
 * SenseNode implementation for an INA219 Shunt sensorI2C 
 * Address: 0x40
 */
class INA219aShuntSensor : public Sense::I2CBusSensor, public Sense::ObservableNode<ShuntValue> {
public:
  INA219aShuntSensor(uint8_t sensorId);
  ~INA219aShuntSensor();

  void initialize() override;
  char* getReadableValue(char* value, uint8_t size) override;

protected:
  void readRawValue() override;

private:
  Adafruit_INA219 ina219;
};
