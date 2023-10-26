#ifndef FlashStorage_h
#define FlashStorage_h

#include "Calibration.h"
#include "Config.h"

#define STORAGE_SIZE 106

class FlashStorage{

  public:
    FlashStorage();
    void load();
    bool getValid();
    Calibration* getCalibration();
    Config* getConfig();
    void save();
  private:
    uint8_t buffer[STORAGE_SIZE];
    bool valid = false;
    Calibration* calib;
    Config* config;
    
  
};




#endif
