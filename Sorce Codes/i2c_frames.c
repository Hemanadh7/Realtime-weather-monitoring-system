#include "header.h"

/*void i2c_byte_write(u8 sa, u8 mr, u8 d)
{
	i2c_start();
	i2c_write(sa);
	i2c_ack();
	i2c_write(mr);
	i2c_ack();
	i2c_write(d);
	i2c_ack();
	i2c_stop();
}*/

u8 i2c_byte_read(u8 sa, u8 mr)
{
	u8 temp;
	i2c_start();
	i2c_write(sa);
	i2c_ack();
	i2c_write(mr);
	i2c_ack();
	i2c_start();
	i2c_write(sa|0x1);
	i2c_ack();
	temp=i2c_read();
	i2c_noack();
	i2c_stop();
	return temp;
}

void i2c_eeprom_byte_write(u8 ha, u8 la, u8 d)
{
	i2c_start();
	i2c_write(0xA0);
	i2c_ack();
	i2c_write(ha);
	i2c_ack();
	i2c_write(la);
	i2c_ack();
	i2c_write(d);
	i2c_ack();
	i2c_stop();
	delay_ms(10);
}

u8 i2c_eeprom_byte_read(u8 ha, u8 la)
{
	u8 temp;
	i2c_start();
	i2c_write(0xA0);
	i2c_ack();
	i2c_write(ha);
	i2c_ack();
	i2c_write(la);
	i2c_ack();
	i2c_start();
	i2c_write(0xA1);
	i2c_ack();
	temp=i2c_read();
	i2c_noack();
	i2c_stop();
	return temp;
}