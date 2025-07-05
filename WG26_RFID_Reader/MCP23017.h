#pragma once


#include <Arduino.h>
#include <Wire.h>


#define MCP23017_I2C_address  0x20

#define MCP23017_IODIRA 			0x00
#define MCP23017_IODIRB 			0x01
#define MCP23017_IPOLA 				0x02
#define MCP23017_IPOLB 				0x03
#define MCP23017_GPINTENA 		0x04
#define MCP23017_GPINTENB 		0x05
#define MCP23017_DEFVALA 			0x06
#define MCP23017_DEFVALB 			0x07
#define MCP23017_INTCONA 			0x08
#define MCP23017_INTCONB 			0x09
#define MCP23017_IOCON 				0x0A
#define MCP23017_GPPUA 				0x0C
#define MCP23017_GPPUB 				0x0D
#define MCP23017_INTFA 				0x0E
#define MCP23017_INTFB 				0x0F
#define MCP23017_INTCAPA 			0x10
#define MCP23017_INTCAPB 			0x11
#define MCP23017_GPIOA 				0x12
#define MCP23017_GPIOB 				0x13
#define MCP23017_OLATA 				0x14
#define MCP23017_OLATB 				0x15


class MCP23017
{
	public:
		MCP23017();
		void begin(void);
		uint8_t read(uint8_t reg);
		void write(uint8_t reg, uint8_t value);

	private:
};
