#ifndef Config_h
#define Config_h

#include "Arduino.h"

class Config
{
    public:
        Config();
        uint32_t getSensorPollingInterval();
        void setSensorPollingInterval(uint32_t val);
        uint32_t getpHupON();
        uint32_t getpHDelay();
        uint32_t getpHdownON();
        uint32_t getECDelay();
        uint32_t getECaON();
        uint32_t getUvON();
        uint32_t getECbON();
        uint32_t getUvOFF();
        uint32_t getPumpON();
        uint32_t getPumpOFF();
        uint32_t getLightON();
        uint32_t getLightOFF();
        uint32_t getAirON();
        uint32_t getAirOFF();
        float getECsetpoint();
        float getPHsetpoint();
        float getECdz();
        float getPHdz();
        void setpHupON(uint32_t indata);
        void setpHDelay(uint32_t indata);
        void setpHdownON(uint32_t indata);
        void setECDelay(uint32_t indata);
        void setECaON(uint32_t indata);
        void setUvON(uint32_t indata);
        void setECbON(uint32_t indata);
        void setUvOFF(uint32_t indata);
        void setPumpON(uint32_t indata);
        void setPumpOFF(uint32_t indata);
        void setLightON(uint32_t indata);
        void setLightOFF(uint32_t indata);
        void setAirON(uint32_t indata);
        void setAirOFF(uint32_t indata);
        void setECsetpoint(float sp);
        void setPHsetpoint(float sp);
        void setECdz(float sp);
        void setPHdz(float sp);
        String getJson();
        
    
    private:
        uint32_t sensorPollingInterval = 1000;
        uint32_t ph_up_on = 10,ph_up_off = 10,ph_dn_on = 10,ph_dn_off = 10,ec_a_on=10,ec_a_off=10,ec_b_on=10,ec_b_off=10,pump_on=60,pump_off=600,air_on=60,air_off=120,light_on=43200,light_off=43200;
        float sp_ec = 1.2,sp_ph = 7.0,ec_dz=0.2,ph_dz=0.5;

    
};

#endif

        
