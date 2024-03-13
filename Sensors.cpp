#include <stdint.h>

#include "Sensors.h"

BH1750 lightMeter;
OneWire oneWire(WATER_TEMP_PIN);
DallasTemperature waterTempSensor(&oneWire);
ModbusMaster node;

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
  this->initWaterSensors();
  
}

void Sensors::initWaterSensors()
{
  Serial2.begin(9600,SERIAL_8N1,16,17,false,20);
  node.begin(2,Serial2);
  //pinMode(SELECTOR_PIN,OUTPUT);
  //digitalWrite(SELECTOR_PIN,this->selector);
}

void Sensors::setEC(int raw_sensor)
{
  int raw = map(raw_sensor,10,1008,0,1023);
  float voltage = raw * (5000.0/1023.0);
  this->raw_ec = voltage;
  float nec = 1000*voltage / 820.0 /200.0;
  float Kval = 1.0;
  if(nec > 2.5)
  {
    Kval = this->calib->getEChigh();
  }
  else if(nec < 2.0)
  {
    Kval = this->calib->getEClow();
  }

  float value = nec * Kval;
  this->ec = value / (1.0+0.185*(this->water_temp - 25.0));
}

float Sensors::getECvoltage()
{
  return this->raw_ec;
}

void Sensors::setPH(int raw_sensor)
{
  int raw = map(raw_sensor,10,1008,0,1023);
  float voltage = raw * (5000.0/1023.0);
  this->raw_ph = voltage;

  float slope = (3.0)/(((this->calib->getPHNeutral() - 2500.0)/3.0) - ((this->calib->getPHAcid()-2500.0)/3.0));
  float intercept = 7.0 - slope * ((this->calib->getPHNeutral() - 2500.0)/3.0);
  this->ph = ((slope * (voltage-2500.0) )/3.0) + intercept;
}

void Sensors::updateSensorBuffer()
{
  unsigned long mill = millis();
  
  if(mill >= this->next_read)
  {
     //Serial.println("fired");
     if(Serial2.available() == 4)
      {
        uint8_t t1=0,t2=0,t3=0,t4=0;
        t1 = Serial2.read();
        t2 = Serial2.read();
        t3 = Serial2.read();
        t4 = Serial2.read();
        uint8_t crc = t2 ^ t3;
        if((t1 == 0xCC)&&(t4 == crc))
        {
          int pd = t2 | t3<<8;
          //Serial.println("got..");
          if((pd>=0) && (pd<=1023))
          {
            this->low_byte = t2;
            this->high_byte = t3;
          }
        }
        
        Serial2.flush();
      }
  }
  else
  {
    Serial2.read();
  }
 
}

void Sensors::updateWaterSensors()
{

    unsigned long mill = millis();

    if(mill >= this->next_read)
    {

 

    int raw = this->low_byte | this->high_byte << 8;
    if(this->selector)
      {
        Serial.print("EC RAW : ");
        Serial.println(raw);
      }
      else
      {
        Serial.print("PH RAW : ");
        Serial.println(raw);
      }
    if(raw <= 1023)
    {
      if(this->selector == true)
      {
        this->setEC(raw);
        this->ec_err = 0;
      }
      else
      {
        this->setPH(raw);
        this->ph_err = 0;
      }
    }
    else
    {
      if(this->selector)
      {
        this->ec_err++;
      }
      else
      {
        this->ph_err++;
      }
    }



  if(this->ph_err >= MAX_ERROR_TRESHOLD)
  {
    this->setPH(0);
  }

  if(this->ec_err >= MAX_ERROR_TRESHOLD)
  {
    this->setEC(0);
  }

   }
  

}


void Sensors::switchSensor()
{
    this->selector = !this->selector;
    //digitalWrite(SELECTOR_PIN,this->selector);
    unsigned long mill = millis();
    
    this->next_read = mill + 1000;
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
  this->updateWaterSensors();
  /*
  Serial.print("Water Temp: ");
  Serial.print(this->water_temp);
  Serial.print(" | Air Temp: ");
  Serial.print(this->air_tempe);
  Serial.print(" | Humidity: ");
  Serial.print(this->humidity);
  Serial.print(" | Light: ");
  Serial.println(this->light);*/
  
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

String Sensors::getJson()
{

  char buff[256];

  int xp = sprintf(buff,
            "{"
            "\"light\": %.2f,"
            "\"air_temp\": %.2f,"
            "\"humidity\": %.2f,"
            "\"ph\": %.2f,"
            "\"ec\": %.2f,"
            "\"water_temp\": %.2f,"
            "\"water_flow\": %.2f,"
            "\"water_level\": %.2f"
            "}",
            light, air_tempe, humidity, ph, ec, water_temp, water_flow, water_level);

  return String(buff);


}
