#ifndef Hydroponics_H
#define Hydroponics_H

#include "Arduino.h"
#include "Actuators.h"
#include "Calibration.h"
#include "Config.h"
#include "Display.h"
#include "FlashStorage.h"
#include "LocalTime.h"
#include "Logger.h"
#include "NetworkConfigs.h"
#include "Sensors.h"
#include "Storage.h"
#include "Process.h"



class Hydroponics
{
private:
    Actuators* actuators;
    Calibration* calibration;
    Config* config;
    Display* display;
    FlashStorage* flashStorage;
    LocalTime* localTime;
    Logger* logger;
    NetworkConfigs* networkConfigs;
    Sensors* sensors;
    Storage* storage;
    Process* process;
    bool loadOK = false;

    
public:
    Hydroponics();
    Actuators* getActuators();
    Calibration* getCalibration();
    Config* getConfig();
    Display* getDisplay();
    FlashStorage* getFlashStorage();
    LocalTime* getLocalTime();
    Logger* getLogger();
    NetworkConfigs* getNetworkConfig();
    Sensors* getSensors();
    Storage* getStorage();
    Process* getProcess();
    bool getLoadOK();
    void init();
    void updateFreeRun();
    void resetConfigDefaults();
    void update1S();
    void update3S();
    String getJSON();
};




#endif
