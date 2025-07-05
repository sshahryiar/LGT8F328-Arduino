#include "I2C_LCD.h"


static uint8_t lcd_ctrl;


I2C_LCD::I2C_LCD()
{
}


void I2C_LCD::begin(void)
{
	lcd_ctrl = 0x00;

	io.begin();
	
#if(LCD_BIT_MODE == LCD_8_bit_mode)
	send((LCD_8_pin_interface | LCD_2_row_display | LCD_5x7_dots), LCD_CMD);
	delay(10);
	send((LCD_8_pin_interface | LCD_2_row_display | LCD_5x7_dots), LCD_CMD);
	delay(10);
	send((LCD_8_pin_interface | LCD_2_row_display | LCD_5x7_dots), LCD_CMD);
#elif(LCD_BIT_MODE == LCD_4_bit_mode)
	send((LCD_4_pin_interface | LCD_2_row_display | LCD_5x7_dots), LCD_CMD);
	delay(10);
	send((LCD_4_pin_interface | LCD_2_row_display | LCD_5x7_dots), LCD_CMD);
	delay(10);
	send((LCD_4_pin_interface | LCD_2_row_display | LCD_5x7_dots), LCD_CMD);	
#endif	

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
#if(LCD_DRIVER_MODEL == DIYMORE)
            lcd_ctrl &= 0x7F;
#elif(LCD_DRIVER_MODEL == ROBOTDYN)
			lcd_ctrl &= 0xDF;
#endif
			break;
		 }
		 case LCD_DAT:
		 {
#if(LCD_DRIVER_MODEL == DIYMORE)
            lcd_ctrl |= 0x82;
#elif(LCD_DRIVER_MODEL == ROBOTDYN)
			lcd_ctrl |= 0x20;
#endif
			break;
		 }
	}

	io.write(MCP23017_GPIOA, lcd_ctrl);
	write_data(value);
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
#if(LCD_DRIVER_MODEL == DIYMORE)
	lcd_ctrl |= 0x22;
#elif(LCD_DRIVER_MODEL == ROBOTDYN)
	lcd_ctrl |= 0x80;
#endif
	io.write(MCP23017_GPIOA, lcd_ctrl);
	delay(1);
#if(LCD_DRIVER_MODEL == DIYMORE)
	lcd_ctrl &= 0xDF;
#elif(LCD_DRIVER_MODEL == ROBOTDYN)
	lcd_ctrl &= 0x7F;
#endif

	io.write(MCP23017_GPIOA, lcd_ctrl);
	delay(1);
}


void I2C_LCD::write_data(uint8_t value)
{
#if(LCD_BIT_MODE == LCD_8_bit_mode)
	io.write(MCP23017_GPIOB, value);
	toggle_EN();
#elif(LCD_BIT_MODE == LCD_4_bit_mode)
	io.write(MCP23017_GPIOB, (value & 0xF0));
	toggle_EN();
	io.write(MCP23017_GPIOB, ((value & 0x0F) << 0x04));
	toggle_EN();
#endif
}