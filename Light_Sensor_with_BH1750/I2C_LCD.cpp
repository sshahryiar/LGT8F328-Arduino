#include "I2C_LCD.h"


static uint8_t bl_state;
static uint8_t data_value;


I2C_LCD::I2C_LCD()
{
}


void I2C_LCD::begin(void)
{
	bl_state = LCD_BL_ON;
  data_value = 0x04;
  
	io.begin();

	io.write(data_value);
	delay(10);
	
	send(0x33, LCD_CMD);
  send(0x32, LCD_CMD);
	
	send((LCD_4_pin_interface | LCD_2_row_display | LCD_5x7_dots), LCD_CMD);
	send((LCD_display_on | LCD_cursor_off | LCD_blink_off), LCD_CMD);
	send((LCD_clear_display), LCD_CMD);
	send((LCD_cursor_direction_inc | LCD_display_no_shift), LCD_CMD);
}


void I2C_LCD::send(uint8_t value, uint8_t mode)
{
	switch(mode)
	{
		 case LCD_CMD:
		 {
			data_value &= 0xF4;
			break;
		 }
		 case LCD_DAT:
		 {
			data_value |= 0x01;
			break;
		 }
	}

	switch(bl_state)
	{
		 case LCD_BL_ON:
		 {
			data_value |= 0x08;
			break;
		 }
		 case LCD_BL_OFF:
		 {
			data_value &= 0xF7;
			break;
		 }
	}
	
	io.write(data_value);
	send_4_bits(value);
	delay(1);
}


void I2C_LCD::clear_home(void)
{
	send(LCD_clear_display, LCD_CMD);
	send(LCD_goto_home, LCD_CMD);
}


void I2C_LCD::gotoxy(uint8_t x_pos, uint8_t y_pos)
{
	switch(y_pos)
	{
		case 1:
		{
			send((0x80 | (LCD_line_2_y_pos + x_pos)), LCD_CMD);
			break;
		}

		case 2:
		{
			send((0x80 | (LCD_line_3_y_pos + x_pos)), LCD_CMD);
			break;
		}

		case 3:
		{
			send((0x80 | (LCD_line_4_y_pos + x_pos)), LCD_CMD);
			break;
		}

		default:
		{
			send((0x80 | (LCD_line_1_y_pos + x_pos)), LCD_CMD);
			break;
		}
	}
}



void I2C_LCD::chr(const char char_data)
{
	send(char_data, LCD_DAT);
}


void I2C_LCD::text(uint8_t x_pos, uint8_t y_pos, const char *lcd_string)
{
		gotoxy(x_pos, y_pos);
    while(*lcd_string != '\0')
    {
        chr(*lcd_string++);
    };
}


void I2C_LCD::toggle_EN(void)
{
	data_value |= 0x04;
	io.write(data_value);
	delay(1);
	data_value &= 0xF9;
	io.write(data_value);
	delay(1);
}


void I2C_LCD::send_4_bits(uint8_t value)
{
	uint8_t tmp = 0x00;

	tmp = (value & 0xF0);
	data_value &= 0x0F;
	data_value |= tmp;
	io.write(data_value);
	toggle_EN();
	
	tmp = (value & 0x0F);
	tmp <<= 0x04;
	data_value &= 0x0F;
	data_value |= tmp;
	io.write(data_value);
	toggle_EN();
}