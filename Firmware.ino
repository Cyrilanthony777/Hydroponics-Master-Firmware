
// Import required libraries
#include <Arduino.h>
#include "Hydroponics.h"
#include "Network.h"
#

unsigned long nextMillis1s = 0;
unsigned long nextMillis3s = 3000;
unsigned long nextMillis15s = 0;
Hydroponics* hydroponics;

TaskHandle_t Task0,Task1;

void thread0(void * params)
{
  
  while(true)
  {
    unsigned long currentMillis = millis();
    hydroponics->updateFreeRun();
  if(currentMillis >= nextMillis1s)
  {
    nextMillis1s = currentMillis + 1000;
    hydroponics->update1S();
  }

  if(currentMillis >= nextMillis3s)
  {
    
    nextMillis3s = currentMillis + 3000;
    hydroponics->update3S();
  }
  }

}

void thread1(void * params)
{
  Serial.println("Network Thread Started");
 Network* network = new Network(hydroponics);
 network->initNetwork();
  const TickType_t xDelay = 15000 / portTICK_PERIOD_MS;
 while(true)
 {
    unsigned long currentMillis = millis();
    
    if(nextMillis15s >= currentMillis)
    {
      nextMillis15s = currentMillis + 15000;
      
    }
    network->doRequest();
    vTaskDelay(xDelay);
 }
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  hydroponics = new Hydroponics();
  hydroponics->init();

  xTaskCreatePinnedToCore(
      thread0, /* Function to implement the task */
      "Task1", /* Name of the task */
      50000,  /* Stack size in words */
      hydroponics,  /* Task input parameter */
      0,  /* Priority of the task */
      &Task0,  /* Task handle. */
      0);

    xTaskCreatePinnedToCore(
      thread1, /* Function to implement the task */
      "Task1", /* Name of the task */
      75000,  /* Stack size in words */
      hydroponics,  /* Task input parameter */
      1,  /* Priority of the task */
      &Task1,  /* Task handle. */
      0);


  
 
}
 
void loop(){

  delay(1000);

  
}
