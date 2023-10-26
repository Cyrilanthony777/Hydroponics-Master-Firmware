#include"Config.h"

Config::Config()
{

}


uint32_t Config::getSensorPollingInterval()
{
    return sensorPollingInterval;
}

void Config::setSensorPollingInterval(uint32_t val)
{
    sensorPollingInterval = val;
}

uint32_t Config::getpHupON()
{
    return ph_up_on;
}

uint32_t Config::getpHupOFF()
{
    return ph_up_off;
}

uint32_t Config::getpHdownON()
{
    return ph_dn_on;
}

uint32_t Config::getpHdownOFF()
{
    return ph_dn_off;
}

uint32_t Config::getECaON()
{
    return ec_a_on;
}

uint32_t Config::getECaOFF()
{
    return ec_a_off;
}

uint32_t Config::getECbON()
{
    return ec_b_on;
}

uint32_t Config::getECbOFF()
{
    return ec_b_off;
}

uint32_t Config::getPumpON()
{
    return pump_on;
}

uint32_t Config::getPumpOFF()
{
    return pump_off;
}

uint32_t Config::getLightON()
{
    return light_on;
}

uint32_t Config::getLightOFF()
{
    return light_off;
}

uint32_t Config::getAirON()
{
    return air_on;
}

uint32_t Config::getAirOFF()
{
    return air_off;
}

float Config::getECsetpoint()
{
    return sp_ec;
}

float Config::getPHsetpoint()
{
    return sp_ph;
}

float Config::getECdz()
{
    return ec_dz;
}

float Config::getPHdz()
{
    return ph_dz;
}

void Config::setpHupON(uint32_t indata)
{
    ph_up_on = indata;
}

void Config::setpHupOFF(uint32_t indata)
{
    ph_up_off = indata;
}

void Config::setpHdownON(uint32_t indata)
{
    ph_dn_on = indata;
}

void Config::setpHdownOFF(uint32_t indata)
{
    ph_dn_off = indata;
}

void Config::setECaON(uint32_t indata)
{
    ec_a_on = indata;
}

void Config::setECaOFF(uint32_t indata)
{
    ec_a_off = indata;
}

void Config::setECbON(uint32_t indata)
{
    ec_b_on = indata;
}

void Config::setECbOFF(uint32_t indata)
{
    ec_b_off = indata;
}

void Config::setPumpON(uint32_t indata)
{
    pump_on = indata;
}

void Config::setPumpOFF(uint32_t indata)
{
    pump_off = indata;
}

void Config::setLightON(uint32_t indata)
{
    light_on = indata;
}

void Config::setLightOFF(uint32_t indata)
{
    light_off = indata;
}

void Config::setAirON(uint32_t indata)
{
    air_on = indata;
}

void Config::setAirOFF(uint32_t indata)
{
    air_off = indata;
}

void Config::setECsetpoint(float sp)
{
    sp_ec = sp;
}

void Config::setPHsetpoint(float sp)
{
    sp_ph = sp;
}

void Config::setECdz(float sp)
{
    ec_dz = sp;
}

void Config::setPHdz(float sp)
{
    ph_dz = sp;
}



