#include "PCF8574.h"


PCF8574::PCF8574()
{
}


void PCF8574::begin(void)
{
	Wire.begin();
	Wire.setClock(400000);
	Wire.flush();
	delay(100);
}


uint8_t PCF8574::read(uint8_t reg)
{
	Wire.beginTransmission(PCF8574_I2C_address); 
	Wire.write(reg); 
	Wire.endTransmission(); 
	Wire.requestFrom(PCF8574_I2C_address, 1); 
	if(Wire.available())
	{
		return Wire.read();
	}
}


void PCF8574::write(uint8_t value)
{
	Wire.beginTransmission(PCF8574_I2C_address); 
	Wire.write(value); 
	Wire.endTransmission(); 
}
