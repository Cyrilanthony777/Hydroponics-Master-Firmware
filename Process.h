#ifndef Process_h
#define Process_h

#include "Arduino.h"

class Process
{
    public:
        Process();
        void init(void);
        void run(void);
        void stop(void);
        void pause(void);
        void resume(void);
        void process(void);
    
    private:
        void processCallback(void);
        int processState = 0;
        bool processRunning = false;
        unsigned long processTime = 0;

    
};

#endif

