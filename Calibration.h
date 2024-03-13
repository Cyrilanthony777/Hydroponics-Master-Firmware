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
    float getPHAcid();
    void setPHAcid(float val);
    float getPHNeutral();
    void setPHNeutral(float val);
    float getEClow();
    void setEClow(float val);
    float getEChigh();
    void setEChigh(float val);
    float getWaterTempCalib();
    void setWaterTempCalib(float val);
    float getWaterFlowCalib();
    void setWaterFlowCalib(float val);
    int calibrateEC(float val,float temp);
    int calibratePH(float val);
    String getJson();
  private:
    float light=0.0,airtemp=0.0,humi=0.0,ph_acid=3378.0,ph_neutral = 2500.0,ec_low=1.0,ec_high=1.0,wt=0.0,flow=0.0;
    
};



#endif
