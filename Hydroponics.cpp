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
    if(this->storage->initStorage())
    {
        this->networkConfigs = new NetworkConfigs(this->storage);
        configInit = this->networkConfigs->initNetworkConfig();
    }
    this->display->setSdOK(this->storage->isStorageOK());
    this->display->setConfigOK(configInit);
    this->loadOK = true;
    this->process = new Process(this->actuators,this->config,this->display,this->sensors);

}

void Hydroponics::update1S()
{
    this->sensors->sensorUpdate();
    this->display->updateDisplay();
    this->process->processCallback();
}

bool Hydroponics::getLoadOK()
{
  return this->loadOK;
}

void Hydroponics::update3S()
{
  this->display->changeScreen();
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