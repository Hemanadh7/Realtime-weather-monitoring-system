#include "header.h"
#include <reg51.h>

sbit SDA=P2^0;
sbit SCL=P2^1;

// MODIFIED CODE FROM DATASHEET
void ds1621_init()
{
	SCL=1;
	SDA=1;
	// Initializing DS1621
	i2c_start();
  i2c_write(0x90);
  i2c_ack();
  i2c_write(0xAC);
  i2c_ack();
  i2c_stop();
	
	// Conversion of temp.
	i2c_start();
	i2c_write(0x90);
	i2c_ack();
	i2c_write(0xEE);
	i2c_ack();
	i2c_stop();
}

s8 ds1621_read()
{
	s8 TH, TL;
	i2c_start();
	i2c_write(0x90);
	i2c_ack();
	i2c_write(0xAA);
	i2c_ack();
	i2c_start();
	i2c_write(0x91);
	i2c_ack();
	TH=i2c_read();
	i2c_ack();
	TL=i2c_read();
	i2c_noack();
	i2c_stop();
	return TH;
}

// CODE FROM DATASHEET
/*void ds1621_init()
{
	SCL=1;
	SDA=1;
	// Initializing DS1621
	i2c_start();
  i2c_write(0x90);
  i2c_ack();
  i2c_write(0xAC);
  i2c_ack();
  //i2c_write(0x02); //// INGNORING AC WRITE
  //i2c_ack();
	//i2c_start(); // CHANGE 0
	i2c_write(0x90); /// ---------- START TH
	i2c_ack();
	i2c_write(0xA1);
	i2c_ack();
	i2c_write(0x28);
	i2c_ack();
	i2c_write(0x00);
	i2c_ack(); /// ------------ END TH
	//i2c_start(); // CHANGE 1
	i2c_write(0x90); /// ---------- START TL
	i2c_ack();
	i2c_write(0xA2);
	i2c_ack();
	i2c_write(0x0A);
	i2c_ack();
	i2c_write(0x00);
	i2c_ack(); /// --------------- END TL
	i2c_stop(); // EXTRA LINE APART FROM DATASHEET - CHANGE 2
	
	// Temperature Conversion
	i2c_start();
	i2c_write(0x90);
	i2c_ack();
	//i2c_start(); // CHANGE 3
	i2c_write(0xEE);
	i2c_ack();
	i2c_stop();
}
*/