#include "Sensors.h"

BH1750 lightMeter;
OneWire oneWire(WATER_TEMP_PIN);
DallasTemperature waterTempSensor(&oneWire);

Sensors::Sensors(Calibration* calib,Config* config)
{
  this->calib = calib;
  this->config = config;
}

void Sensors::init(void)
{
  sensorPollingInterval = config->getSensorPollingInterval();
  Wire.begin();
  this->initClimateSensor();
  this->light_sensor_ok = lightMeter.begin();
  this->initWaterTempSensor();
  
}

void Sensors::initWaterTempSensor()
{
   waterTempSensor.begin();
   uint8_t count = waterTempSensor.getDeviceCount();
   delay(100);
   if(count > 0)
   {
    this->water_temp_sensor_ok = true;
    Serial.println("Water Temperature Sensor OK");
   }
   else
   {
    this->water_temp_sensor_ok = false;
    Serial.println("Water Temperature Sensor FAILED!!!!");
   }
}

void Sensors::updateWaterTempSensor()
{
  if(this->water_temp_sensor_ok)
  {
    waterTempSensor.requestTemperatures();
    this->water_temp = waterTempSensor.getTempCByIndex(0);
  }
}

void Sensors::initClimateSensor(void)
{
  Wire.beginTransmission(CLIMATE_SENSOR_ADDR);
  int error = Wire.endTransmission();
  if(error == 0)
  {
    temp_humi_sensor_ok = true;
    Serial.println("Climate Sensor Init OK");
  }
  else
  {
    temp_humi_sensor_ok = false;
    Serial.println("Climate Sensor Init Error");
  }

}

void Sensors::updateClimateSensor(void)
{
  if(this->temp_humi_sensor_ok)
  {
    Wire.beginTransmission(CLIMATE_SENSOR_ADDR);
    Wire.write(0x2C);
    Wire.write(0x06);
    Wire.endTransmission();
    delay(1);
    Wire.requestFrom(CLIMATE_SENSOR_ADDR, 6);
    uint8_t data[6];
    while(Wire.available() < 6){};
    if(Wire.available() == 6)
    {
      for(int i = 0; i < 6; i++)
      {
        data[i] = Wire.read();
      }
    }
    this->humidity = ((((data[3] * 256.0) + data[4]) * 100) / 65535.0);
    this->air_tempe = ((((data[0] * 256.0) + data[1]) * 175) / 65535.0) - 45;

  }
}

void Sensors::updateLightSensor(void)
{
  if(this->light_sensor_ok)
  {
    this->light = lightMeter.readLightLevel();
  }
}

void Sensors::sensorUpdate(void)
{
  this->updateClimateSensor();
  this->updateLightSensor();
  this->updateWaterTempSensor();
  Serial.print("Water Temp: ");
  Serial.print(this->water_temp);
  Serial.print(" | Air Temp: ");
  Serial.print(this->air_tempe);
  Serial.print(" | Humidity: ");
  Serial.print(this->humidity);
  Serial.print(" | Light: ");
  Serial.println(this->light);
  
}


float Sensors::getLight(void)
{
  return light;
}

float Sensors::getAirTemp(void)
{
  return air_tempe;
}

float Sensors::getHumidity(void)
{
  return humidity;
}

float Sensors::getPH(void)
{
  return ph;
}

float Sensors::getWaterTemp(void)
{
  return water_temp;
}

float Sensors::getWaterFlow(void)
{
  return water_flow;
}

float Sensors::getEC(void)
{
  return ec;
}
