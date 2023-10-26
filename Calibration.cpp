#include "Arduino.h"
#include "Calibration.h"


Calibration::Calibration()
{
  
}


float Calibration::getLightCalib()
{
  return light;
}

void Calibration::setLightCalib(float val)
{
  light = val;
}

float Calibration::getAirTempCalib()
{
  return airtemp;
}

void Calibration::setAirTempCalib(float val)
{
  airtemp = val;
}

float Calibration::getHumidityCalib()
{
  return humi;
}

void Calibration::setHumidityCalib(float val)
{
  humi = val;
}

float Calibration::getPHCalib()
{
  return ph;
}

void Calibration::setPHCalib(float val)
{
  ph = val;
}

float Calibration::getECCalib()
{
  return ec;
}

void Calibration::setECCalib(float val)
{
  ec = val;
}

float Calibration::getWaterTempCalib()
{
  return wt;
}

void Calibration::setWaterTempCalib(float val)
{
  wt = val;
}

float Calibration::getWaterFlowCalib()
{
  return flow;
}

void Calibration::setWaterFlowCalib(float val)
{
  flow = val;
}
