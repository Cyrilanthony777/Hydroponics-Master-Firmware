#include "esp32-hal-gpio.h"
#include "Actuators.h"


Actuators::Actuators()
{
  pinMode(PIN_PUMP, OUTPUT);
  pinMode(PIN_UV, OUTPUT_OPEN_DRAIN);
  pinMode(PIN_LIGHT, OUTPUT_OPEN_DRAIN);
  pinMode(PIN_AIR, OUTPUT_OPEN_DRAIN);
  pinMode(PIN_EC_A, OUTPUT);
  pinMode(PIN_EC_B, OUTPUT);
  pinMode(PIN_PH_UP, OUTPUT);
  pinMode(PIN_PH_DN, OUTPUT);

  digitalWrite(PIN_PUMP, LOW);
  digitalWrite(PIN_UV, HIGH);
  digitalWrite(PIN_LIGHT, HIGH);
  digitalWrite(PIN_AIR, HIGH);
  digitalWrite(PIN_EC_A, LOW);
  digitalWrite(PIN_EC_B, LOW);
  digitalWrite(PIN_PH_UP, LOW);
  digitalWrite(PIN_PH_DN, LOW);
  

}

void Actuators::setAir(bool state)
{
  this->aerator = state;
  digitalWrite(PIN_AIR, !state);  
}
void Actuators::setPump(bool state)
{
  this->pump = state;
  digitalWrite(PIN_PUMP, state);  
}

void Actuators::setUV(bool state)
{
  this->uv = state;
  digitalWrite(PIN_UV, !state);  
}


void Actuators::setLight(bool state)
{
  this->light = state;
  digitalWrite(PIN_LIGHT, !state);  
}

void Actuators::setEcA(bool state)
{
  this->ec_a = state;
  digitalWrite(PIN_EC_A, state);
}

void Actuators::setEcB(bool state)
{
  this->ec_b = state;
  digitalWrite(PIN_EC_B, state);
}

void Actuators::setPhDn(bool state)
{
  this->ph_dn = state;
  digitalWrite(PIN_PH_DN, state);
}

void Actuators::setPhUp(bool state)
{
  this->ph_up = state;
  digitalWrite(PIN_PH_UP, state);
}

bool Actuators::getPump()
{
  return this->pump;
}
bool Actuators::getLight(){
  return this->light;
}

bool Actuators::getAir()
{
  return this->aerator;
}

bool Actuators::getUV()
{
  return this->uv;
}

bool Actuators::getPhUp()
{
  return this->ph_up;
}

bool Actuators::getPhDn()
{
  return this->ph_dn;
}

bool Actuators::getEcA()
{
  return this->ec_a;
}

bool Actuators::getEcB()
{
  return this->ec_b;
}

void Actuators::stopAll()
{
  this->setPump(false);
  this->setLight(false);
  this->setAir(false);
  this->setUV(false);
  this->setEcA(false);
  this->setEcB(false);
  this->setPhUp(false);
  this->setPhDn(false);
}

String Actuators::getJson()
{

  char json_data[256];

  int xp = sprintf(json_data, "{\"pump\":%d,\"ph_up\":%d,\"ph_dn\":%d,\"ec_a\":%d,\"ec_b\":%d,\"light\":%d,\"air\":%d,\"uv\":%d}",
            pump ? 1 : 0,
            ph_up ? 1 : 0,
            ph_dn ? 1 : 0,
            ec_a ? 1 : 0,
            ec_b ? 1 : 0,
            light ? 1 : 0,
            aerator ? 1 : 0,
            uv ? 1 : 0);

  return String(json_data);
}