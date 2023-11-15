#include "Network.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>
#include "SPIFFS.h"

AsyncWebServer server(80);

Network::Network(Hydroponics* hydro)
{
  this->hydroponics = hydro;
}

String Network::getJsonData()
{
  return this->hydroponics->getSensors()->getJson();
}

bool Network::initNetwork()
{
  Serial.println("Loading Network...");
  WiFi.mode(WIFI_STA);
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return false;
  }
  else
  {
    Serial.println("Spiffs OK");
  }
  
  while(!this->hydroponics->getLoadOK())
  {
    delay(1000);
  }

  while(!this->hydroponics->getNetworkConfig()->isNetworkConfigOK())
  {
    delay(1000);
  }

  Serial.print("Connecting to SSID : ");
  Serial.println(this->hydroponics->getNetworkConfig()->getSSID());
  
  WiFi.begin(this->hydroponics->getNetworkConfig()->getSSID().c_str(),this->hydroponics->getNetworkConfig()->getPassword().c_str());

  
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  Serial.println("Connected :)");
  Serial.println(WiFi.localIP());
  this->hydroponics->getDisplay()->setWifiOK(true);
  Serial.println(this->hydroponics->getSensors()->getJson());


  server.on("/sensors", HTTP_GET, [&](AsyncWebServerRequest *request){
    
    
    request->send(200, "application/json",this->hydroponics->getSensors()->getJson());
  });

  server.begin();





  return true;
}