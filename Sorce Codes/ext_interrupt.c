#include "header.h"
#include <reg51.h>
extern u8 entries, sa;
u8 fData[13], i;
void INT0_Handler(void) interrupt 0
{
	i=1;
	sa=0;
	fData[9]=0;
	uart_string_tx("ID    DATE       TIME       LDR  POT   TEMP\r");
	Read_EEPROM();
	uart_tx('\r');
}

void en_ext_interrupt(void)
{
	EA=1;
	EX0=1;
	IT0=1;
}

void Read_EEPROM(void)
{
	for(sa=0;i<entries;i++,sa=sa+12)
	{
		(i/10==0)?uart_tx(' '):uart_tx(i/10+48);
		uart_tx(i%10+48);
		uart_string_tx("  ");
		fData[0]=i2c_eeprom_byte_read(0,sa+0); 	// Hours
		fData[1]=i2c_eeprom_byte_read(0,sa+1); 	// Minutes
		fData[2]=i2c_eeprom_byte_read(0,sa+2); 	// A/P in Period
		fData[3]=i2c_eeprom_byte_read(0,sa+3); 	// Vout(LDR)
		fData[4]=i2c_eeprom_byte_read(0,sa+4); 	// Vout1(POT)
		fData[5]=i2c_eeprom_byte_read(0,sa+5); 	// TEMP[0]
		fData[6]=i2c_eeprom_byte_read(0,sa+6); 	// TEMP[1]
		fData[7]=i2c_eeprom_byte_read(0,sa+7); 	// TEMP[2]
		fData[8]=i2c_eeprom_byte_read(0,sa+8); 	// TEMP[3]
		fData[10]=i2c_eeprom_byte_read(0,sa+9); // Day
		fData[11]=i2c_eeprom_byte_read(0,sa+10);// Month
		fData[12]=i2c_eeprom_byte_read(0,sa+11);// Seconds
		uart_tx(fData[10]/16+48);
		uart_tx(fData[10]%16+48);
		uart_tx('/');
		uart_tx(fData[11]/16+48);
		uart_tx(fData[11]%16+48);
		uart_tx('/');
		uart_tx('2');														// Hardcoded Year value as it is 2020 next few months anyway
		uart_tx('0');
		uart_string_tx("  ");
		uart_tx(fData[0]/16+48);
		uart_tx(fData[0]%16+48);
		uart_tx(':');
		uart_tx(fData[1]/16+48);
		uart_tx(fData[1]%16+48);
		uart_tx(':');
		uart_tx(fData[12]/16+48);
		uart_tx(fData[12]%16+48);
		uart_tx(' ');
		uart_tx(fData[2]);
		uart_tx('M');
		uart_string_tx("   ");
		uart_tx(fData[3]/10+48);
		uart_tx(fData[3]%10+48);
		uart_tx('%');
		uart_string_tx("  ");
		uart_tx(fData[4]/10+48);
		uart_tx(fData[4]%10+48);
		uart_tx('V');
		uart_string_tx("  ");
		uart_string_tx(fData+5);
		uart_tx('C');
		uart_tx('\r');
	}
}