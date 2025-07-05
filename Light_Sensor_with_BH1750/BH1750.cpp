#include "BH1750.h"


BH1750::BH1750()
{
}


void BH1750::begin(void)
{
	Wire.begin();
	Wire.setClock(400000);
	Wire.flush();
	delay(100);

	write(BH1750_power_up);
	write(BH1750_reset);
	write(BH1750_power_down);
	delay(100);
}


uint16_t BH1750::get_lux(void)
{
	uint16_t lx = 0;

	lx = get_reading(BH1750_cont_H_res_mode_1, 150);
	lx = (((float)lx) / 1.2);

	return lx;
}


void BH1750::write(uint8_t cmd)
{
  Wire.beginTransmission(BH1750_I2C_address); 
  Wire.write(cmd);          
  Wire.endTransmission(); 
}


uint16_t BH1750::read_word(void)
{
	uint8_t hb = 0;
	uint8_t lb = 0;
	uint16_t value = 0;

	Wire.beginTransmission(BH1750_I2C_address); 
	Wire.requestFrom(BH1750_I2C_address, 2); 
	if(Wire.available() <= 2)
	{
		hb = Wire.read();
		lb = Wire.read();
	}

	Wire.endTransmission(); 

	value = hb;
	value << 8;
	value |= lb;

	return value;
} 


uint16_t BH1750::get_reading(uint8_t mode, uint16_t delay_time)
{
	uint16_t lx = 0;
	
	write(BH1750_power_up);
	write(mode);
	lx = read_word();
	delay(delay_time);
	write(BH1750_power_down);

	return lx;
}