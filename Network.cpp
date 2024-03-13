#include "WiFiClient.h"
#include "Network.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>
#include <HTTPClient.h>
#include "SPIFFS.h"

AsyncWebServer server(80);
HTTPClient httpclient;
WiFiClient wificlient;

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
  this->connected = true;
  Serial.println(this->hydroponics->getSensors()->getJson());


  server.on("/sensors", HTTP_GET, [&](AsyncWebServerRequest *request){
    request->send(200, "application/json",this->hydroponics->getSensors()->getJson());
  });

  server.on("/config", HTTP_GET, [&](AsyncWebServerRequest *request){
    request->send(200, "application/json",this->hydroponics->getConfig()->getJson());
  });

  server.on("/actuators", HTTP_GET, [&](AsyncWebServerRequest *request){
    request->send(200, "application/json",this->hydroponics->getActuators()->getJson());
  });

  server.on("/hydro", HTTP_GET, [&](AsyncWebServerRequest *request){
    request->send(200, "application/json",this->hydroponics->getJSON());
  });

  server.on("/start", HTTP_GET, [&](AsyncWebServerRequest *request){
    this->hydroponics->getProcess()->run();
    request->send(200, "text/plain","OK");
  });

  server.on("/stop", HTTP_GET, [&](AsyncWebServerRequest *request){
    this->hydroponics->getProcess()->stop();
    request->send(200, "text/plain","OK");
  });

  server.on("/calib/ec", HTTP_GET, [&](AsyncWebServerRequest *request){
    int result = this->hydroponics->getCalibration()->calibrateEC(this->hydroponics->getSensors()->getECvoltage(), this->hydroponics->getSensors()->getWaterTemp());
    if(result == 1)
    {
      this->hydroponics->getFlashStorage()->save();
      request->send(200, "text/plain","Found 1.413 uS/cm Solution. Calibration Successful");
    }
    else if(result == 2)
    {
      this->hydroponics->getFlashStorage()->save();
      request->send(200, "text/plain","Found 12.88 mS/cm Solution. Calibration Successful");
    }
    else
    {
      
      request->send(200, "text/plain","Unknown Solution. Calibration Failed!!!!");
    }
  });

  server.on("/config_reset", HTTP_GET, [&](AsyncWebServerRequest *request){
    if(this->hydroponics->getProcess()->isRunning())
    {
      request->send(200, "text/plain","Stop The process first");
    }
    else
    {

      this->hydroponics->resetConfigDefaults();
      request->send(200, "text/plain","Config Reset OK");
    }
    
    
  });

  server.begin();





  return true;
}

void Network::doRequest()
{
  if(this->connected == true)
  {
    httpclient.begin(wificlient,this->request_url);
    httpclient.setTimeout(3000);
    httpclient.addHeader("Content-Type","application/json");
    Serial.println("Doing HTTP REQUEST");
    int response_code = httpclient.POST(this->hydroponics->getJSON());
    Serial.println(response_code);
    if(response_code == HTTP_CODE_OK)
    {
      this->hydroponics->getDisplay()->setInetOk(true);
      Serial.println("HTTP OK");
    }
    else
    {
      this->hydroponics->getDisplay()->setInetOk(false);
      Serial.println("HTTP FAIL");
    }

    httpclient.end();
    Serial.println("FINISH HTTP REQUEST");


  }
  
}