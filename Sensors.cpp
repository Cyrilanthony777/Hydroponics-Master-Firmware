#include <stdint.h>

#include "Sensors.h"

 union{
    uint32_t dataValue;
    float floatValue;
  }floatConverter;

Sensors::Sensors(Calibration* calib,Config* config)
{
  this->calib = calib;
  this->config = config;
}

void Sensors::init(void)
{
  Serial2.begin(115200,SERIAL_8N1,16,17,false,20);
  sensorPollingInterval = config->getSensorPollingInterval();
  this->initClimateSensor();
  this->initWaterTempSensor();
  this->initWaterSensors();
  
}

void Sensors::initWaterSensors()
{
  
  
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


void Sensors::nodesCallback()
{

}

void Sensors::updateSensorBuffer()
{
  
  if(Serial2.available()>0)
  {
    uint8_t buffer[20];
    int size = Serial2.readBytes(buffer,20);
    if(size > 7)
    {
      for(int x=0;x<size;x++)
      {
        Serial.print(buffer[x],HEX);
        Serial.print(",");
        
      }
      Serial.println("");
      uint8_t crc = 0x00;
      if((buffer[0] == 0xAA)&&(buffer[1] == 0xCC)&&(buffer[4] == 0xBA))
      {
        if((buffer[5] < 8)&&(buffer[5] > 0))
        {
          for(int i=0;i<=(5+buffer[5]);i++)
          {
            crc ^= buffer[i];
          }
        
          uint8_t index = 6+buffer[5];

          if(buffer[index] == crc)
          {
            if(buffer[3] == 0x01)
            {

              uint32_t airTemp = buffer[6] | (buffer[7] << 8) | (buffer[8] << 16) | (buffer[9] << 24);
              uint16_t lightRaw = buffer[11] | (buffer[12] << 8);
              floatConverter.dataValue = airTemp;
              this->air_tempe = floatConverter.floatValue;
              this->humidity = buffer[10];
              this->light = lightRaw;

            }
            else if(buffer[3] == 0x02)
            {
              uint32_t waterTemp = buffer[6] | (buffer[7] << 8) | (buffer[8] << 16) | (buffer[9] << 24);
              
              floatConverter.dataValue = waterTemp;
              this->water_temp = floatConverter.floatValue;
              uint16_t conductivity = buffer[10] | (buffer[11] << 8);
              this->setEC(map(conductivity,0,65535,0,1023));
            }
            else if(buffer[3] == 0x03)
            {
              uint32_t phRaw = buffer[6] | (buffer[7] << 8) | (buffer[8] << 16) | (buffer[9] << 24);
              floatConverter.dataValue = phRaw;
              this->ph = floatConverter.floatValue;
              this->water_level = buffer[10];
            }
          } 
        }
      } 
    }

  }
  
 
}

void Sensors::updateWaterSensors()
{

   

}


void Sensors::switchSensor()
{
   
}

void Sensors::initWaterTempSensor()
{
   
}

void Sensors::updateWaterTempSensor()
{

}

void Sensors::initClimateSensor(void)
{


}

void Sensors::updateClimateSensor(void)
{

}

void Sensors::updateLightSensor(void)
{

}

void Sensors::sensorUpdate(void)
{
  uint8_t outBuffer[] = {0xAA,0xCC,0,0,0xAB,0,0};
  if(this->currentNode >= this->connected)
  {
    this->currentNode = 0;
  }

  if(this->currentNode < this->connected)
  {

    outBuffer[2] = this->address[this->currentNode];
    outBuffer[3] = this->nodes[this->currentNode];
    
    for(int i=0;i<6;i++)
    {
      outBuffer[6] ^= outBuffer[i];
    }
    
    Serial2.write(outBuffer,7);
    this->errors[this->currentNode]++;
  }

  this->currentNode++;

  
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
