#include <reg51.h>
#include "header.h"

void uart_init(u32 baud)
{
	SCON=0x50;
	TMOD|=0x20;
	switch(baud)
	{
		case 7200: TH1=252; break;
		case 9600: TH1=253; break;
		case 14400: TH1=254; break;
		case 28800: TH1=255; break;
		case 57600: TH1=255; PCON=(1<<7); break;
		default: TH1=253;
	}
	TR1=1;
}

void uart_tx(u8 d)
{
	SBUF=d;
	while(TI==0);
	TI=0;
}

void uart_string_tx(const s8* str)
{
	while(*str)
	{
		SBUF=*str;
		while(TI==0);
		TI=0;
		str++;
	}
}