#include "BH1750.h"
#include "I2C_LCD.h"


BH1750 lx_sensor;
I2C_LCD display;


char buffer[20];
uint8_t i = 0;
uint16_t pt = 0;
uint16_t lux = 0;


void setup(void) 
{
  pinMode(13, OUTPUT);
  lx_sensor.begin();
  display.begin();
  display.clear_home();
  display.text(0, 0, "Lux/lx:");
}


void loop(void) 
{
  lux = lx_sensor.get_lux();
  sprintf(buffer, "%5d ", lux);
  display.text(11, 0, buffer);

  pt = map(lux, 1, 1000, 1, 15);
  pt = constrain(pt, 1, 1000);

  display.text(0, 1, "               ");
  for(i = 0; i < pt; i++)
  {
    display.text(i, 1, ">");
    delay(1);
  }

  delay(600);
}
