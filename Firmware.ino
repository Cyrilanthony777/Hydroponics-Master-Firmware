
// Import required libraries
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>
#include "SPIFFS.h"
#include "Hydroponics.h"

unsigned long nextMillis1s = 0;
unsigned long nextMillis3s = 3000;
Hydroponics* hydroponics;

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  hydroponics = new Hydroponics();
  hydroponics->init();

  
 
}
 
void loop(){

  unsigned long currentMillis = millis();
  if(currentMillis >= nextMillis1s)
  {
    nextMillis1s = currentMillis + 1000;
    hydroponics->update1S();
  }

  if(currentMillis >= nextMillis3s)
  {
    hydroponics->update3S();
    nextMillis3s = currentMillis + 3000;
  }

  
}
