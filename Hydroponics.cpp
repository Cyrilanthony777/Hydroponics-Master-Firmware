#include "Hydroponics.h"

Hydroponics::Hydroponics()
{
    
    this->actuators = new Actuators();
    this->flashStorage = new FlashStorage();
    this->localTime = new LocalTime();
    this->logger = new Logger();
    this->network = new Network();
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

}

void Hydroponics::update1S()
{
    this->sensors->sensorUpdate();
    this->display->updateDisplay();
}

void Hydroponics::update3S()
{
  this->display->changeScreen();
}
