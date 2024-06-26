#include "Hydroponics.h"

Hydroponics::Hydroponics()
{
    
    this->actuators = new Actuators();
    this->flashStorage = new FlashStorage();
    this->localTime = new LocalTime();
    this->logger = new Logger();
    this->storage = new Storage();

  
}

void Hydroponics::init()
{
    bool configInit = false;
    this->flashStorage->load();
    this->calibration = this->flashStorage->getCalibration();
    this->config = this->flashStorage->getConfig();
    this->sensors = new Sensors(this->calibration,this->config);
    this->sensors->init();
    this->display = new Display(this->sensors);
    this->display->initDisplay();
    Serial.println("Here1");
    if(this->storage->initStorage())
    {
        Serial.println("Storage OK");
        this->networkConfigs = new NetworkConfigs(this->storage);
        Serial.println("NETWORK OK");
        configInit = this->networkConfigs->initNetworkConfig();
        Serial.println("HereX");
    }
    Serial.println("Here2");
    this->display->setSdOK(this->storage->isStorageOK());
    Serial.println("Here3");
    this->display->setConfigOK(configInit);
    Serial.println("Here4");
    this->loadOK = true;
    this->process = new Process(this->actuators,this->config,this->display,this->sensors);

}

void Hydroponics::update1S()
{
    this->sensors->sensorUpdate();
    this->display->updateDisplay();
    this->process->processCallback();
}

void Hydroponics::resetConfigDefaults()
{
  this->config = new Config();
  this->flashStorage->setConfig(this->config);
  this->flashStorage->save();
}

bool Hydroponics::getLoadOK()
{
  return this->loadOK;
}

void Hydroponics::updateFreeRun()
{
  this->sensors->updateSensorBuffer();
}

void Hydroponics::update3S()
{
  this->display->changeScreen();
  this->sensors->switchSensor();
}

Actuators* Hydroponics::getActuators()
{
  return this->actuators;
}

Calibration* Hydroponics::getCalibration()
{
  return this->calibration;
}

Config* Hydroponics::getConfig()
{
  return this->config;
}

Display* Hydroponics::getDisplay()
{
  return this->display;
}

FlashStorage* Hydroponics::getFlashStorage()
{
  return this->flashStorage;
}

LocalTime* Hydroponics::getLocalTime()
{
  return this->localTime;
}

Logger* Hydroponics::getLogger()
{
  return this->logger;
}

NetworkConfigs* Hydroponics::getNetworkConfig()
{
  return this->networkConfigs;
}

Sensors* Hydroponics::getSensors()
{
  return this->sensors;
}

Storage* Hydroponics::getStorage()
{
  return this->storage;
}

Process* Hydroponics::getProcess()
{
  return this->process;
}

String Hydroponics::getJSON()
{
  char buff[2048];

  int xp = sprintf(buff,
            "{"
            "\"api_key\": \"%s\","
            "\"running\": %d,"
            "\"sensors\": %s,"
            "\"config\": %s,"
            "\"actuators\": %s"
            "}",
            this->networkConfigs->getApiKey().c_str(), (this->process->isRunning()?1:0), this->sensors->getJson().c_str(), this->config->getJson().c_str(), this->actuators->getJson().c_str()
            );

  return String(buff);
}