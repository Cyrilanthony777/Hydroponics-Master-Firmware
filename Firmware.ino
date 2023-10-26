
// Import required libraries
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>
#include "SPIFFS.h"
#include "Hydroponics.h"

unsigned long nextMillis = 0;
Hydroponics* hydroponics;

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  hydroponics = new Hydroponics();
  hydroponics->init();

  
 
}
 
void loop(){

  unsigned long currentMillis = millis();
  if(currentMillis >= nextMillis)
  {
    nextMillis = currentMillis + 1000;
    hydroponics->update1S();
  }

  
}
