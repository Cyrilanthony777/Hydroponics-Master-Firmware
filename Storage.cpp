#include "Storage.h"

Storage::Storage()
{
  
}

bool Storage::initStorage()
{
  if(!SD.begin()){
      isOK = false;
      return false;
  }
 uint8_t cardType = SD.cardType();
  if(cardType == CARD_NONE){
      isOK = false;
      return false;
  }

  isOK = true;
  return true;
}


bool Storage::isStorageOK()
{
  return isOK;
}


String Storage::readFile(String fname)
{
  if(!isOK){
    return "";
  }
  File file = SD.open(fname);
  if(!file){
    return "";
  }
  String content = "";
  while(file.available()){
    content += (char)file.read();
  }
  file.close();
  return content;
}


bool Storage::writeFile(String fname,String content,String header)
{
  if(!isOK){
    return false;
  }
  File file = SD.open(fname,FILE_APPEND);
  if(!file){
    file = SD.open(fname,FILE_WRITE);
    if(file)
    {
      file.print(header);
    }
    else
    {
      return false;
    }
  }
  file.print(content);
  file.close();
  return true;
}



