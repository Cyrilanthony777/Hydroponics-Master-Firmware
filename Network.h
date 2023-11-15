#ifndef Network_H
#define Network_H

#include <ESPAsyncWebSrv.h>
#include "SPIFFS.h"
#include "Hydroponics.h"

class Network
{
private:
    bool isOK = false;
    bool spiffsOK = false;
    Hydroponics* hydroponics;
    
public:
    Network(Hydroponics *hydro);
    bool initNetwork();
    String getJsonData();
    
};




#endif


