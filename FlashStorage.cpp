#include "FlashStorage.h"
#include <EEPROM.h>


FlashStorage::FlashStorage()
{
  EEPROM.begin(STORAGE_SIZE);
  calib = new Calibration();
  config = new Config();
}

void FlashStorage::load()
{
  union{
    uint32_t dataValue;
    float floatValue;
  }floatConverter;

  
  uint16_t crc = 0x00;
  for(int i=0;i<STORAGE_SIZE;i++)
  {
    buffer[i] = EEPROM.read(i);
    
    if(i>=(STORAGE_SIZE-3))
    {
      crc ^= buffer[i];
    }
  }


  if((buffer[104] == (crc & 0xFF))&&(buffer[105] == (crc >> 8)))
  {
    valid = true;
  }
  else
  {
    valid = false;
  }


  if(valid)
  {

    uint32_t out_data[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    int count = 0;
    for(int i=0;i<26;i++)
    {
      out_data[i] = buffer[count] | (buffer[count+1] << 8) | (buffer[count+2] << 16) | (buffer[count+3] << 24);
      count += 4;
    }

    floatConverter.dataValue = out_data[0];
    calib->setLightCalib(floatConverter.floatValue);
    floatConverter.dataValue = out_data[1];
    calib->setAirTempCalib(floatConverter.floatValue);
    floatConverter.dataValue = out_data[2];
    calib->setHumidityCalib(floatConverter.floatValue);
    floatConverter.dataValue = out_data[3];
    calib->setPHCalib(floatConverter.floatValue);
    floatConverter.dataValue = out_data[4];
    calib->setECCalib(floatConverter.floatValue);
    floatConverter.dataValue = out_data[5];
    calib->setWaterTempCalib(floatConverter.floatValue);
    floatConverter.dataValue = out_data[6];
    calib->setWaterFlowCalib(floatConverter.floatValue);
    config->setSensorPollingInterval(out_data[7]);
    config->setpHupON(out_data[8]);
    config->setpHDelay(out_data[9]);
    config->setpHdownON(out_data[10]);
    config->setECDelay(out_data[11]);
    config->setECaON(out_data[12]);
    config->setUvON(out_data[13]);
    config->setECbON(out_data[14]);
    config->setUvOFF(out_data[15]);
    config->setPumpON(out_data[16]);
    config->setPumpOFF(out_data[17]);
    config->setLightON(out_data[18]);
    config->setLightOFF(out_data[19]);
    config->setAirON(out_data[20]);
    config->setAirOFF(out_data[21]);
    floatConverter.dataValue = out_data[22];
    config->setECsetpoint(floatConverter.floatValue);
    floatConverter.dataValue = out_data[23];
    config->setPHsetpoint(floatConverter.floatValue);
    floatConverter.dataValue = out_data[24];
    config->setECdz(floatConverter.floatValue);
    floatConverter.dataValue = out_data[25];
    config->setPHdz(floatConverter.floatValue);
  }
}

bool FlashStorage::getValid()
{
  return valid;
}

void FlashStorage::save()
{
  union{
    uint32_t dataValue;
    float floatValue;
  }floatConverter;

  
  uint32_t in_data[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  uint8_t buffer_temp[STORAGE_SIZE];
  floatConverter.floatValue = calib->getLightCalib();
  in_data[0] = floatConverter.dataValue;
  floatConverter.floatValue = calib->getAirTempCalib();
  in_data[1] = floatConverter.dataValue;
  floatConverter.floatValue = calib->getHumidityCalib();
  in_data[2] = floatConverter.dataValue;
  floatConverter.floatValue = calib->getPHCalib();
  in_data[3] = floatConverter.dataValue;
  floatConverter.floatValue = calib->getECCalib();
  in_data[4] = floatConverter.dataValue;
  floatConverter.floatValue = calib->getWaterTempCalib();
  in_data[5] = floatConverter.dataValue;
  floatConverter.floatValue = calib->getWaterFlowCalib();
  in_data[6] = floatConverter.dataValue;
  in_data[7] = config->getSensorPollingInterval();
  in_data[8] = config->getpHupON();
  in_data[9] = config->getpHDelay();
  in_data[10] = config->getpHdownON();
  in_data[11] = config->getECDelay();
  in_data[12] = config->getECaON();
  in_data[13] = config->getUvON();
  in_data[14] = config->getECbON();
  in_data[15] = config->getUvOFF();
  in_data[16] = config->getPumpON();
  in_data[17] = config->getPumpOFF();
  in_data[18] = config->getLightON();
  in_data[19] = config->getLightOFF();
  in_data[20] = config->getAirON();
  in_data[21] = config->getAirOFF();
  floatConverter.floatValue =config->getECsetpoint();
  in_data[22] = floatConverter.dataValue;
  floatConverter.floatValue = config->getPHsetpoint();
  in_data[23] = floatConverter.dataValue;
  floatConverter.floatValue = config->getECdz();
  in_data[24] = floatConverter.dataValue;
  floatConverter.floatValue = config->getPHdz();
  in_data[25] = floatConverter.dataValue;
  uint16_t crc = 0x00;
  for(int i=0;i<26;i++)
  {
    buffer_temp[i*4] = in_data[i] & 0xFF;
    buffer_temp[i*4+1] = (in_data[i] >> 8) & 0xFF;
    buffer_temp[i*4+2] = (in_data[i] >> 16) & 0xFF;
    buffer_temp[i*4+3] = (in_data[i] >> 24) & 0xFF;
  }
  for(int i=0;i<(STORAGE_SIZE-3);i++)
  {
   crc ^= buffer_temp[i];
  }
  buffer_temp[104] = crc & 0xFF;
  buffer_temp[105] = crc >> 8;
 
  for(int i=0;i<STORAGE_SIZE;i++)
  {
    EEPROM.write(i,buffer_temp[i]);
    
  }
 
  EEPROM.commit();
  

}


Calibration* FlashStorage::getCalibration()
{
  return calib;
}

Config* FlashStorage::getConfig()
{

  return config;
}
