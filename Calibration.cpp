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

float Calibration::getPHAcid()
{
  return this->ph_acid;
}

void Calibration::setPHAcid(float val)
{
  this->ph_acid = val;
}

float Calibration::getPHNeutral()
{
  return this->ph_neutral;
}

void Calibration::setPHNeutral(float val)
{
  this->ph_neutral = val;
}

float Calibration::getEClow()
{
  return ec_low;
}

void Calibration::setEClow(float val)
{
  this->ec_low = val;
}

float Calibration::getEChigh()
{
  return this->ec_high;
}

void Calibration::setEChigh(float val)
{
  this->ec_high = val;
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

int Calibration::calibrateEC(float voltage,float temp)
{
  int ret = 0;
  float raw_ec = 1000.0*voltage/820.0/200.0;
  if((raw_ec >= 0.9) && (raw_ec <=1.9))
  {
    float compensation = 1.413*(1.0+0.0185*(temp-25.0));
    this->ec_low = 820.0*200.0*compensation/1000.0/voltage;
    ret = 1;
  }
  else if((raw_ec >= 9.0)&&(raw_ec <= 16.8))
  {
    float compensation = 12.88*(1.0+0.0185*(temp-25.0));
    this->ec_high = 820.0*200.0*compensation/1000.0/voltage;
    ret = 2;
  }

  return ret;

}

int Calibration::calibratePH(float raw)
{
  
}


