#ifndef Calibration_h
#define Calibration_h

#include "Arduino.h"

class Calibration
{
  public:
    Calibration();
    float getLightCalib();
    void setLightCalib(float val);
    float getAirTempCalib();
    void setAirTempCalib(float val);
    float getHumidityCalib();
    void setHumidityCalib(float val);
    float getPHCalib();
    void setPHCalib(float val);
    float getECCalib();
    void setECCalib(float val);
    float getWaterTempCalib();
    void setWaterTempCalib(float val);
    float getWaterFlowCalib();
    void setWaterFlowCalib(float val);
  private:
    float light=0.0,airtemp=0.0,humi=0.0,ph=0.0,ec=0.0,wt=0.0,flow=0.0;
    
};



#endif
