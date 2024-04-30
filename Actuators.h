#ifndef Actuators_H
#define Actuators_H
#include "pindefs.h"
#include "Arduino.h"
class Actuators
{
private:
    bool pump = false;
    bool light = false;
    bool aerator = false;
    bool uv = false;
    bool ph_up = false;
    bool ph_dn = false;
    bool ec_a = false;
    bool ec_b = false;
public:
    Actuators();
    void setPump(bool state);
    void setLight(bool state);
    void setAir(bool state);
    void setUV(bool state);
    void setPhUp(bool state);
    void setPhDn(bool state);
    void setEcA(bool state);
    void setEcB(bool state);

    bool getPump();
    bool getLight();
    bool getAir();
    bool getUV();
    bool getPhUp();
    bool getPhDn();
    bool getEcA();
    bool getEcB();
    
    void stopAll();
    String getJson();


    
};


#endif