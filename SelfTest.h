#ifndef SelfTest_h
#define SelfTest_h

#include "Storage.h"
#include "NetworkConfigs.h"
#include "FlashStorage.h"
#include "Calibration.h"
#include "Config.h"


class SelfTest
{
private:
    void testLocalStorage();
    void testStorage();
    void testNetworkConfig();
    
public:
    SelfTest();
    void performSelfTest();
};






#endif