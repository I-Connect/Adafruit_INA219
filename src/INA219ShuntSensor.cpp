//
//
//

#include "INA219ShuntSensor.h"
#include "SenseUtils.h"

INA219aShuntSensor::INA219aShuntSensor(uint8_t sensorId) : SenseI2CBusSensor(sensorId) {
}

INA219aShuntSensor::~INA219aShuntSensor() {
}

float INA219aShuntSensor::getValueAsFloat() {
  return lastValues.getCurrent_mA();
}

char* INA219aShuntSensor::getValueAsChar(char* value, uint8_t size) {
  return lastValues.asChars(value);
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
  lastValues.setShuntVoltage_mV(sv / SAMPLES);
  lastValues.setBusVoltage_V(bv / SAMPLES);
  lastValues.setCurrent_mA(c / SAMPLES);
  csSerialPrint(F("Current: "));
  csSerialPrint(lastValues.getCurrent_mA());
  csSerialPrintln(" mA");
}

void INA219aShuntSensor::initialize() {
  ina219.begin();
  ina219.setCalibration_Ext_16V_75mV_50A();
  sensorActive = true;
  SenseI2CBusSensor::initialize();
}

byte* INA219aShuntSensor::getValueInBuffer(byte* buffer) {
  memcpy(buffer, &lastValues, sizeof(ShuntValue));
  return buffer;
}

byte INA219aShuntSensor::getMinBufferSize() {
  return sizeof(ShuntValue);
}
