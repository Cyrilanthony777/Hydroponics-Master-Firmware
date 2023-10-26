#ifndef Sensors_h
#define Sensors_h

#include "Arduino.h"
#include "Calibration.h"
#include "Config.h"
#include "pindefs.h"
#include <Wire.h>
#include <BH1750.h>


#define CLIMATE_SENSOR_ADDR 0x44



class Sensors
{
  public:
    Sensors(Calibration* calib,Config* config);
    void init(void);
    float getLight(void);
    float getAirTemp(void);
    float getHumidity(void);
    float getPH(void);
    float getWaterTemp(void);
    float getWaterFlow(void);
    float getEC(void);
    void sensorUpdate(void);


  private:
    Calibration* calib;
    Config* config;
    int sensorPollingInterval = 1000;
    void flowCallback(void);
    float light = 0.0;
    float air_tempe = 0.0;
    float humidity = 0.0;
    float ph = 0.0;
    float ec = 0.0;
    float water_temp = 0.0;
    float water_flow = 0.0;
    bool light_sensor_ok = false;
    bool temp_humi_sensor_ok = false;
    bool water_temp_sensor_ok = false;
    void initClimateSensor(void);
    void updateClimateSensor(void);
    void updateLightSensor(void);
    
  
};


#endif
