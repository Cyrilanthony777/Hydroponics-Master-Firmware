#ifndef Sensors_h
#define Sensors_h

#include "Arduino.h"
#include "Calibration.h"
#include "Config.h"
#include "pindefs.h"
#include <Wire.h>
#include <BH1750.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ModbusMaster.h>
//#include <HardwareSerial.h>

#define CLIMATE_SENSOR_ADDR 0x44
#define MAX_ERROR_TRESHOLD 3



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
    float getECvoltage(void);
    void sensorUpdate(void);
    void updateSensorBuffer();
    void switchSensor();
    String getJson();


  private:
    Calibration* calib;
    Config* config;
    int sensorPollingInterval = 1000;
    void flowCallback(void);
    bool selector = false;
    float light = 0.0;
    float air_tempe = 0.0;
    float humidity = 0.0;
    float ph = 0.0;
    float ec = 0.0;
    float water_temp = 0.0;
    float water_flow = 0.0;
    float water_level = 0.0;
    bool light_sensor_ok = false;
    bool temp_humi_sensor_ok = false;
    bool water_temp_sensor_ok = false;
    int ph_err =0,ec_err=0;
    float raw_ec = 0,raw_ph = 0;
    uint8_t low_byte = 0;
    uint8_t high_byte = 0;
    unsigned long next_read = 0;
    void initClimateSensor(void);
    void updateClimateSensor(void);
    void updateLightSensor(void);
    void initWaterTempSensor(void);
    void updateWaterTempSensor(void);
    void initWaterSensors(void);
    void updateWaterSensors(void);
    void nodesCallback(void);
    void setPH(int raw);
    void setEC(int raw);
    
  
};


#endif
