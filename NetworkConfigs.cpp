#include "NetworkConfigs.h"

NetworkConfigs::NetworkConfigs(Storage* store)
{
    storage = store;
}

bool NetworkConfigs::initNetworkConfig()
{
    if(!storage->isStorageOK()){
        isOK = false;
        return false;
    }
    String content = storage->readFile("/config.txt");
    if(content == ""){
        isOK = false;
        return false;
    }
    String ssid = "";
    String password = "";
    String apiKey = "";
    int i = 0;
    while(content[i] != '\n'){
        if(content[i] != '\r')
        {
          ssid += content[i];
        }
        
        i++;
    }
    i++;
    while(content[i] != '\n'){
      if(content[i] != '\r')
        {
          password += content[i];
        }
        i++;
    }
    i++;
    while(content[i] != '\n'){
      if(content[i] != '\r')
        {
        apiKey += content[i];
        }
        i++;
    }
    this->ssid = ssid;
    this->password = password;
    this->apiKey = apiKey;

    Serial.println(ssid);
    Serial.println(password);
    isOK = true;
    return true;
}

bool NetworkConfigs::isNetworkConfigOK()
{
    return isOK;
}

String NetworkConfigs::getSSID()
{
    return ssid;
}

String NetworkConfigs::getPassword()
{
    return password;
}

String NetworkConfigs::getApiKey()
{
    return apiKey;
}


