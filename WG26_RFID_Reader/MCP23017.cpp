#include "MCP23017.h"


MCP23017::MCP23017()
{
}


void MCP23017::begin(void)
{
	Wire.begin();
	Wire.setClock(400000);
	Wire.flush();
	delay(100);
	
	write(MCP23017_IOCON, 0x18);
	write(MCP23017_IODIRA, 0x00);
	write(MCP23017_IODIRB, 0x00);
	write(MCP23017_GPIOA, 0x00);
	write(MCP23017_GPIOB, 0x00);
}


uint8_t MCP23017::read(uint8_t reg)
{
	Wire.beginTransmission(MCP23017_I2C_address); 
	Wire.write(reg); 
	Wire.endTransmission(); 
	Wire.requestFrom(MCP23017_I2C_address, 1); 
	if(Wire.available())
	{
		return Wire.read();
	}
}


void MCP23017::write(uint8_t reg, uint8_t value)
{
	Wire.beginTransmission(MCP23017_I2C_address); 
	Wire.write(reg); 
	Wire.write(value); 
	Wire.endTransmission(); 
}
