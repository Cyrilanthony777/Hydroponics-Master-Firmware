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
    bool connected = false;
    
    Hydroponics* hydroponics;
    const char* request_url = "http://europe-central2-ecommerce-tools-355909.cloudfunctions.net/function-1/";
    
public:
    Network(Hydroponics *hydro);
    bool initNetwork();
    String getJsonData();
    void doRequest();
    
};




#endif


