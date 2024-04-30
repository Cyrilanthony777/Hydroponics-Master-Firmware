#ifndef NetworkConfigs_h
#define NetworkConfigs_h

#include "Storage.h"

class NetworkConfigs
{
    public:
        NetworkConfigs(Storage* store);
        bool initNetworkConfig();
        bool isNetworkConfigOK();
        String getSSID();
        String getPassword();
        String getApiKey();
    
    private:
        Storage* storage;
        String ssid = "";
        String password = "";
        String apiKey = "";
        bool isOK = false;
};

#endif
