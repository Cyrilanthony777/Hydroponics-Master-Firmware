#ifndef LocalTime_h
#define LocalTime_h
#include <Wire.h>
//#include <TimeLib.h>
//#include <DS1307RTC.h>

class LocalTime{
  public:
    LocalTime();
    String getFileName();

  private:
    String file_name = "data_start";
    
};


#endif
