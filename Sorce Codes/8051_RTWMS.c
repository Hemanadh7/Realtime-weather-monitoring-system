#include <reg51.h>
#include "header.h"
u8 entries;
u8 h, m, s, dt, mn;
u8 Vout, Vout1, temp[6], sa;
u8 period[]={'A','M',0};
u16 adcOut;
main()
{
	entries=1;
	uart_init(9600);								// Initializing UART
	lcd_init();											// Initializing LCD
	ds1621_init();									// Initializing DS1621 Temperature sensor
	en_ext_interrupt();							// Initializing INT0
	set_lcd();
	temp[5]=0;
	while(1)
	{
		// ---------------------Timer display
		h=i2c_byte_read(0xD0, 0x2);		// Reading Hours Register from DS1307
		m=i2c_byte_read(0xD0, 0x1);		// Reading Minutes Register from DS1307
		s=i2c_byte_read(0xD0, 0x0);		// Reading Seconds Register from DS1307
		dt=i2c_byte_read(0xD0, 0x4);	// Reading Date Register from DS1307
		mn=i2c_byte_read(0xD0, 0x5);	// Reading Month Register from DS1307
		if(h==0x12)										// Converting 24-hour format to 12-hour format starts							
			period[0]='P';
		else if(h>=0x13)
		{
			h=h-0x12;
			if(h>=0x0A)
				h=h-0x06;
			if(h>=0x0A)
				h=h+0x06;
			period[0]='P';
		}															// Hour Format (period) conversion ends
		display_time();								// Displaying the Time in LCD
		// ---------------------Temperature display
		set_temp();										// Setting the temperature string(temp)
		lcd_cmd(0xCB);
		lcd_string(temp);							// Displaying the Temperature in LCD
		// ---------------------LDR Display		
		adcOut=read_adc(0,0);					// Reading ADC_OUTPUT from CH0
		Vout=(((float)adcOut)/4095)*100;
		lcd_cmd(0x9B);
		lcd_data(Vout/10+48);					// Displaying LDR intensity in LCD
		lcd_data(Vout%10+48);
		lcd_data('%');
		// ---------------------POT Display
		adcOut=read_adc(0,1);					// Reading ADC_OUTPUT from CH1
		Vout1=((float)adcOut/4095)*99;// Vref = 100v
		lcd_cmd(0xDB);
		lcd_data(Vout1/10+48);				// Displaying POT Vout in LCD
		lcd_data(Vout1%10+48);
		lcd_data('V');
		// ---------------------STORING IN EEPROM (ID, (h,m,s,period), Vout, Vout1, temp)
		if(s==0&&entries<=11) 		// Updating EEPROM every 60 seconds
		{
			Write_EEPROM();							// Writing into the EEPROM
		}
		else if(entries>11)						// Resetting after 10 writings into EEPROM
		{
			entries=1;
			sa=0;
		}
	}
}

void Write_EEPROM(void)
{
	i2c_eeprom_byte_write(0,sa+0,h);				// Hours
	i2c_eeprom_byte_write(0,sa+1,m);				// Minutes
	i2c_eeprom_byte_write(0,sa+2,period[0]);// Period(AM/PM)
	i2c_eeprom_byte_write(0,sa+3,Vout);			// Intensity
	i2c_eeprom_byte_write(0,sa+4,Vout1);		// POT Vout
	i2c_eeprom_byte_write(0,sa+5,temp[0]);	// Temperature string
	i2c_eeprom_byte_write(0,sa+6,temp[1]);
	i2c_eeprom_byte_write(0,sa+7,temp[2]);
	i2c_eeprom_byte_write(0,sa+8,temp[3]);
	i2c_eeprom_byte_write(0,sa+9,dt);				// Date
	i2c_eeprom_byte_write(0,sa+10,mn);			// Minutes
	i2c_eeprom_byte_write(0,sa+11,s);				// Seconds
	sa=sa+12;
	entries=entries+1;
}