#include "Display.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Display::Display(Sensors* sensors)
{
  this->sensors = sensors;
}

void Display::drawScreen1()
{
    display.setFont(NULL);
    display.setCursor(43, 16);
    display.print("CLIMATE");
    display.setCursor(0, 27);
    display.print("Temperature :");
    display.setCursor(0, 40);
    display.print("Humidity    :");
    display.setCursor(0, 53);
    display.print("Light       :");
    display.setCursor(80, 27);
    display.print(this->sensors->getAirTemp());
    display.setCursor(80, 40);
    display.print(this->sensors->getHumidity());
    display.setCursor(80, 53);
    display.print(this->sensors->getLight());
}

void Display::drawScreen2()
{
    display.setFont(NULL);
    display.setCursor(43, 16);
    display.print(" WATER");
    display.setCursor(0, 27);
    display.print("EC          :");
    display.setCursor(0, 40);
    display.print("pH          :");
    display.setCursor(0, 53);
    display.print("Water Temp  :");
    display.setCursor(80, 27);
    display.print(this->sensors->getEC());
    display.setCursor(80, 40);
    display.print(this->sensors->getPH());
    display.setCursor(80, 53);
    display.print(this->sensors->getWaterTemp());
}

bool Display::initDisplay()
{
  Wire.begin();
 if(display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    this->isOK = true;
    Serial.println("Display Init OK");
    return true;
  }
  else
  {
    this->isOK = false;
    Serial.println("Display Init Failed");
    return false;
  }
}

void Display::drawHeader()
{
  display.setCursor(0,0);
  int x_pos = 0; 
  if(!this->sdOK)
  {
    display.drawBitmap(x_pos, 0, NO_SD, 16, 16, WHITE);
    x_pos += 20;
  }

  if(!this->configOK)
  {
    display.drawBitmap(x_pos, 0, NO_CONFIG, 16, 16, WHITE);
    x_pos += 20;
  }

  if(!this->wifiOK)
  {
    display.drawBitmap(x_pos, 0, NO_WIFI, 16, 16, WHITE);
    x_pos += 20;
  }
  else
  {
    display.drawBitmap(x_pos, 0, WIFI_OK, 16, 16, WHITE);
    x_pos += 20;
  }

  if(!this->inetOk)
  {
    display.drawBitmap(x_pos, 0, NO_INT, 16, 16, WHITE);
    x_pos += 20;
  }

  if(this->isRunning)
  {
    display.drawBitmap(110, 0, RUN_ICON, 16, 16, WHITE);
    
  }
  else
  {
    display.drawBitmap(110, 0, STOP_ICON, 16, 16, WHITE);
    
  }

}

void Display::updateDisplay()
{
  if(this->isOK)
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    this->drawHeader();
    if(this->screen == 1)
    {
      this->drawScreen1();
    }
    else
    {
      this->drawScreen2();
    }
    
    display.display();

  }
}

void Display::changeScreen()
{
  if(this->screen == MAX_SCREEN)
  {
    this->screen = 1;
  }
  else
  {
    this->screen++;
  }
}




void Display::setConfigOK(bool configOK)
{
  this->configOK = configOK;
}

void Display::setSdOK(bool sdOK)
{
  this->sdOK = sdOK;
}

void Display::setWifiOK(bool wifiOK)
{
  this->wifiOK = wifiOK;
}

void Display::setInetOk(bool inetOk)
{
  this->inetOk = inetOk;
}

void Display::setRunning(bool isRunning)
{
  this->isRunning = isRunning;
}
