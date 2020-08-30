//
//
//

#include "INA219ShuntSensor.h"
#include "SenseUtils.h"

INA219aShuntSensor::INA219aShuntSensor(uint8_t sensorId) : Sense::I2CBusSensor(), Sense::ObservableNode<ShuntValue>(sensorId) {
}

INA219aShuntSensor::~INA219aShuntSensor() {
}

char* INA219aShuntSensor::getReadableValue(char* value, uint8_t size) {
  return getSingleValue().asChars(value);
}

void INA219aShuntSensor::readRawValue() {
#define SAMPLES 10.0
  float sv = 0;
  float bv = 0;
  float c  = 0;
  for (uint8_t i = 0; i < trunc(SAMPLES); i++) {
    sv = +ina219.getShuntVoltage_mV();
    bv += ina219.getBusVoltage_V();
    c += ina219.getCurrent_mA();
    delay(5);
  }
  ShuntValue lastValues;
  lastValues.setShuntVoltage_mV(sv / SAMPLES);
  lastValues.setBusVoltage_V(bv / SAMPLES);
  lastValues.setCurrent_mA(c / SAMPLES);
  setSingleValue(lastValues, false);
  csSerialPrint(F("Current: "));
  csSerialPrint(lastValues.getCurrent_mA());
  csSerialPrintln(" mA");
}

void INA219aShuntSensor::initialize() {
  ina219.begin();
  ina219.setCalibration_Ext_16V_75mV_50A();
  sensorActive = true;
  Sense::ObservableNode<ShuntValue>::initialize();
}

