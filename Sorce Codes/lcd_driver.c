#include "header.h"
#include <reg51.h>
sbit RS = P3^4;
sbit RW = P3^5;
sbit EN = P3^6;
sfr LCD_PORT = 0x80;

void lcd_init()
{
	lcd_cmd(0x2);
	lcd_cmd(0x38);
	lcd_cmd(0xE);
	lcd_cmd(0x1);
}

void lcd_cmd(u8 cmd)
{
	LCD_PORT = cmd;
	RS = 0;
	RW = 0;
	EN = 1;
	delay_ms(2);
	EN = 0;
}

void lcd_data(u8 ch)
{
	LCD_PORT = ch;
	RS = 1;
	RW = 0;
	EN = 1;
	delay_ms(2);
	EN = 0;
}

void lcd_string(s8* s)
{
	while(*s)
	{
		lcd_data(*s);
		s++;
	}
}