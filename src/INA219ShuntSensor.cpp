//
//
//

#include "INA219ShuntSensor.h"
#include "SenseUtils.h"

INA219aShuntSensor::INA219aShuntSensor(uint8_t sensorId, bool _externalShunt) : Sense::I2CBusSensor(), Sense::ObservableNode<ShuntValue>(sensorId) {
  externalShunt = _externalShunt;
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
    takeI2CSemaphore();
    sv = +ina219.getShuntVoltage_mV();
    bv += ina219.getBusVoltage_V();
    c += ina219.getCurrent_mA();
    giveI2CSemaphore();
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
  csSerialPrint(F("Voltage: "));
  csSerialPrint(lastValues.getBusVoltage());
  csSerialPrintln(" V");
}

void INA219aShuntSensor::initialize() {
  takeI2CSemaphore();
  ina219.begin();
  if(externalShunt){
    ina219.setCalibration_Ext_16V_75mV_50A();
  }
  giveI2CSemaphore();
  sensorActive = true;
  Sense::ObservableNode<ShuntValue>::initialize();
}

