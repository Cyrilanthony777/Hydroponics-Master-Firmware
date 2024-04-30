#include "esp32-hal-timer.h"
#include "Process.h"

Process::Process(Actuators* act,Config* conf,Display* disp,Sensors* sens)
{
  this->actuators = act;
  this->config = conf;
  this->display = disp;
  this->sensors = sens;
}


bool Process::isRunning()
{
  return this->processRunning;
}


void Process::init()
{
  
   

}

void Process::stop()
{
  this->processRunning = false;
}

void Process::run()
{
  this->actuators->setLight(true);
  this->actuators->setPump(true);
  this->actuators->setAir(true);
  this->actuators->setUV(true);
  this->processRunning = true;
  this->display->setRunning(true);
}


void Process::processCallback()
{
  if(this->processRunning == true)
  {
    this->processLights();
    this->processPump();
    this->processAir();
    this->processUV();
    this->processEC();
    this->stopInit = true;
  }

  if(this->processRunning == false)
  {
      if(this->stopInit == true)
      {
        this->actuators->stopAll();
        this->display->setRunning(false);
        light_time =0;
        pump_time=0;
        uv_time=0;
        air_time=0;
        ph_up = 0;
        ph_dn=0;
        ec_a=0;
        ec_b=0;
        ph_time=0;
        ec_time=0;
        ph_delay_b = false;
        ec_delay_b=false;
        stopInit = false;
      }
  }

  
}


void Process::processLights()
{
  if( (actuators->getLight() == true) && (this->light_time >= this->config->getLightON()))
  {
    this->actuators->setLight(false);
    this->light_time = 0;
  }

  if( (actuators->getLight() == false) && (this->light_time >= this->config->getLightOFF()))
  {
    this->actuators->setLight(true);
    this->light_time = 0;
  }


  this->light_time++;

}


void Process::processAir()
{
  if( (actuators->getAir() == true) && (this->air_time >= this->config->getAirON()))
  {
    this->actuators->setAir(false);
    this->air_time = 0;
  }

  if( (actuators->getAir() == false) && (this->air_time >= this->config->getAirOFF()))
  {
    this->actuators->setAir(true);
    this->air_time = 0;
  }


  this->air_time++;

}

void Process::processUV()
{
  if( (actuators->getUV() == true) && (this->uv_time >= this->config->getUvON()))
  {
    this->actuators->setUV(false);
    this->uv_time = 0;
  }

  if( (actuators->getUV() == false) && (this->uv_time >= this->config->getUvOFF()))
  {
    this->actuators->setUV(true);
    this->uv_time = 0;
  }


  this->uv_time++;

}

void Process::processPump()
{
  if( (actuators->getPump() == true) && (this->pump_time >= this->config->getPumpON()))
  {
    this->actuators->setPump(false);
    this->pump_time = 0;
  }

  if( (actuators->getPump() == false) && (this->pump_time >= this->config->getPumpOFF()))
  {
    this->actuators->setPump(true);
    this->pump_time = 0;
  }


  this->pump_time++;

}


void Process::processEC()
{
  float dose_value = this->sensors->getEC() - this->config->getECdz();

  if((dose_value < this->config->getECsetpoint()) && (this->ec_delay_b == false))
  {
    this->actuators->setEcA(true);
    this->actuators->setEcB(true);
    this->ec_delay_b = true;
  }

  if(this->actuators->getEcA() == true)
  {
    this->ec_a++;
  }

  if(this->actuators->getEcB() == true)
  {
    this->ec_b++;
  }

  if(this->ec_a >= this->config->getECaON())
  {
    this->actuators->setEcA(false);
    this->ec_a = 0;
  }

  if(this->ec_b >= this->config->getECbON())
  {
    this->actuators->setEcB(false);
    this->ec_b = 0;
  }

  if(this->ec_delay_b == true)
  {
    this->ec_time++;
  }

  if((this->ec_time >= this->config->getECDelay())&&(this->ec_delay_b == true))
  {
    this->ec_time = 0;
    this->ec_delay_b = false;
  }
}