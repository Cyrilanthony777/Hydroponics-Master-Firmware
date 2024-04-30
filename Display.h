#ifndef Display_h
#define Display_h

#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Sensors.h"
#include "Storage.h"
#include "Icons.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
#define MAX_SCREEN 2

class Display{

  public:
    Display(Sensors* sensors);
    bool initDisplay();
    void updateDisplay();
    void setConfigOK(bool configOK);
    void setSdOK(bool sdOK);
    void setWifiOK(bool wifiOK);
    void setInetOk(bool inetOk);
    void setRunning(bool isRunning);
    void changeScreen();
  private:
    void drawHeader();
    void drawScreen1();
    void drawScreen2();
    Sensors* sensors;
    int screen =1;
    int x_padding = 0;
    bool isOK = false;
    bool configOK = false;
    bool sdOK = false;
    bool wifiOK = false;
    bool inetOk = false;
    bool isRunning = false;
};

#endif
