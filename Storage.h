#ifndef Storage_h
#define Storage_h

#include "FS.h"
#include "SD.h"
#include "SPI.h"

class Storage
{
  public:
    Storage();
    bool initStorage();
    bool isStorageOK();
    String readFile(String filename);
    bool writeFile(String filename,String content,String header);
    
    
  private:
    bool isOK = false;
    bool error = false;

};
#endif
