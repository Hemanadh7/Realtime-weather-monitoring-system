#include "header.h"
extern u8 h, m, s;
extern u8 period[3], temp[6];

void delay_ms(u16 ms)
{
	u8 i;
	for( ; ms > 0; ms--)
	{
		for(i = 250; i > 0; i--);
		for(i = 247; i > 0; i--);
	}
}

void display_time()
{
	lcd_cmd(0x80);
	lcd_data(h/16+48);
	lcd_data(h%16+48);
	lcd_data(':');
	lcd_data(m/16+48);
	lcd_data(m%16+48);
	lcd_data(':');
	lcd_data(s/16+48);
	lcd_data(s%16+48);
	lcd_data(' ');
	lcd_string(period);
}

void set_lcd(void)
{
	lcd_cmd(0x0C);
	lcd_cmd(0xC0);
	lcd_string("Temp.     :0"); // display temp@ 0xCB
	lcd_cmd(0x90);
	lcd_string("Intensity :0"); // display @0x9B
	lcd_cmd(0xD0);
	lcd_string("Voltage   :0"); // display @0xDB
}

void set_temp()
{
	s8 TH=ds1621_read();
	if((TH&(1<<7)))
	{
		TH=~TH;
		TH=TH+1;
		temp[0]='-';
		temp[1]=TH/100+48;
		temp[2]=((TH/10)%10)+48;
		temp[3]=TH%10+48;
	}
	else
	{
		temp[0]='+';
		temp[1]=TH/100+48;
		temp[2]=((TH/10)%10)+48;
		temp[3]=TH%10+48;
	}
	temp[4]='C';
}