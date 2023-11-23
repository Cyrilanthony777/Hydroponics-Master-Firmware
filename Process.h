#include "esp32-hal-timer.h"
#ifndef Process_h
#define Process_h

#include "Arduino.h"
#include "Sensors.h"
#include "Actuators.h"
#include "Config.h"
#include "Display.h"

class Process
{
    public:
        Process(Actuators* act,Config* conf,Display* disp,Sensors* sens);
        void init(void);
        void run(void);
        void stop(void);
        void pause(void);
        void resume(void);
        bool isRunning();
        void processCallback(void);
    
    private:
        
        void processLights();
        void processPump();
        void processUV();
        void processAir();
        void processPH();
        void processEC();
        Config* config;
        Sensors* sensors;
        Actuators* actuators;
        Display* display;
        int processState = 0;
        bool processRunning = false,ph_delay_b = false,ec_delay_b=false,stopInit = false;
        unsigned long processTime = 0;
        uint32_t light_time =0, pump_time=0,uv_time=0,air_time=0,ph_up = 0,ph_dn=0,ec_a=0,ec_b=0,ph_time=0,ec_time=0;
        hw_timer_t *process_timer = NULL;


    
};

#endif

