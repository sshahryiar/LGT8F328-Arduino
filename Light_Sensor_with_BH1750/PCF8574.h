#pragma once


#include <Arduino.h>
#include <Wire.h>


#define PCF8574_I2C_address     0x27


class PCF8574
{
	public:
		PCF8574();
		void begin(void);
		uint8_t read(uint8_t reg);
		void write(uint8_t value);
		
	private:
};