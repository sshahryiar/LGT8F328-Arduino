#pragma once


#include <Arduino.h>
#include "MCP23017.h"


/*

Pin out of MCP23017 to LCD

DIYMORE MCP23017 1602/2004/12864 I2C LCD Driver Module Pin Mapping
------------------------------------------------------------------

GPIOA
    A7   A6   A5   A4   A3   A2   A1   A0
    RS   RW   EN   X    X    X    GND  X

GPIOB
    B7   B6   B5   B4   B3   B2   B1   B0
    D7   D6   D5   D4   D3   D2   D1   D0


ROBOTDYN MCP23017 1602/2004/12864 I2C LCD Driver Module Pin Mapping
-------------------------------------------------------------------

GPIOA
    A7   A6   A5   A4   A3   A2   A1   A0
    EN   RW   RS   X    L-   L+   X    X

GPIOB
    B7   B6   B5   B4   B3   B2   B1   B0
    D7   D6   D5   D4   D3   D2   D1   D0

*/


#define LCD_clear_display            0x01
#define LCD_goto_home                0x02

#define LCD_cursor_direction_inc     0x06
#define LCD_cursor_direction_dec     0x04
#define LCD_display_shift            0x05
#define LCD_display_no_shift         0x04

#define LCD_display_on               0x0C
#define LCD_display_off              0x0A
#define LCD_cursor_on                0x0A
#define LCD_cursor_off               0x08
#define LCD_blink_on                 0x09
#define LCD_blink_off                0x08

#define LCD_8_pin_interface          0x30
#define LCD_4_pin_interface          0x20
#define LCD_2_row_display            0x28
#define LCD_1_row_display            0x20
#define LCD_5x10_dots                0x60
#define LCD_5x7_dots                 0x20

#define LCD_line_1_y_pos             0x00
#define LCD_line_2_y_pos             0x40
#define LCD_line_3_y_pos             0x14
#define LCD_line_4_y_pos             0x54

#define LCD_DAT                      1
#define LCD_CMD                      0

#define DIYMORE                  	 	 1
#define ROBOTDYN                 	 	 0

#define LCD_8_bit_mode           	 	 1
#define LCD_4_bit_mode           	   0

#define LCD_BIT_MODE             	 	 LCD_8_bit_mode
#define LCD_DRIVER_MODEL           	 DIYMORE


class I2C_LCD
{
	public:
		I2C_LCD();
		void begin(void);
		void send(uint8_t value, uint8_t mode);
		void clear_home(void);
		void gotoxy(uint8_t x_pos, uint8_t y_pos);
		void chr(const char char_data);
		void text(uint8_t x_pos, uint8_t y_pos, const char *lcd_string);
		
	private:
		MCP23017 io;
		void toggle_EN(void);
		void write_data(uint8_t value);
};