#include "SelfTest.h"

SelfTest::SelfTest()
{
  
}


void SelfTest::performSelfTest()
{
  testStorage();
  testLocalStorage();
  testNetworkConfig();
}

void SelfTest::testStorage()
{
    Serial.println("######### Testing Storage #########");
  Storage* storage = new Storage();
  if(storage->initStorage())
  {
    Serial.println("Storage OK");
  }
  else
  {
    Serial.println("Storage NOT OK");
  }
  delete storage;
  
}

void SelfTest::testLocalStorage()
{
    Serial.println("######### Testing LocalStorage #########");
  FlashStorage* flashStorage = new FlashStorage();
  flashStorage->load();
  if(flashStorage->getValid())
  {
    Serial.println("FlashStorage OK");
  }
  else
  {
    Serial.println("FlashStorage NOT OK");
  }
  delete flashStorage;
}

void SelfTest::testNetworkConfig()
{
  Serial.println("######### Testing NetworkConfig #########");
  Storage* storage = new Storage();

  if(storage->initStorage())
  {
    Serial.println("Storage OK");
    NetworkConfigs* networkConfig = new NetworkConfigs(storage);
    if(networkConfig->initNetworkConfig())
    {
      Serial.println("NetworkConfig OK");
      Serial.print("SSID : ");
      Serial.println(networkConfig->getSSID());
      Serial.print("PASSWORD : ");
      Serial.println(networkConfig->getPassword());
      Serial.print("KEY : ");
      Serial.println(networkConfig->getApiKey());
    }
    else
    {
      Serial.println("NetworkConfig NOT OK");
    }
  }
  else
  {
    Serial.println("Storage NOT OK");
  }
    
  delete storage;
  
}
