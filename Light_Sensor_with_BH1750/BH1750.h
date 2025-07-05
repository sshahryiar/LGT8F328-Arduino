#pragma once


#include <Arduino.h>
#include <Wire.h>


#define	BH1750_I2C_address				0x23  
         
#define	BH1750_power_down				0x00
#define BH1750_power_up					0x01
#define BH1750_reset					0x07 
#define BH1750_cont_H_res_mode_1  		0x10 
#define BH1750_cont_H_res_mode_2  		0x11  
#define BH1750_cont_L_res_mode   		0x13                                          
#define BH1750_one_time_H_res_mode_1  	0x20 
#define BH1750_one_time_H_res_mode_2  	0x21
#define BH1750_one_time_L_res_mode  	0x23   


class BH1750
{
	public:
		BH1750();
		void begin(void);
		uint16_t get_lux(void);   

	private:
		void write(uint8_t cmd);
		uint16_t read_word(void);  
		uint16_t get_reading(uint8_t mode, uint16_t delay_time);     
};