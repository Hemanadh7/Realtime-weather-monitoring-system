typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u16;
typedef signed int s16;
typedef unsigned long u32;
typedef signed long s32;

#define PORT0 0
#define PORT1 1
#define PORT2 2
#define PORT3 3

// GENERAL PURPOSE
void DecToString(u16,u8*);
void delay_ms(u16);

// EXTRA FUNCTIONS AND VARIABLES USED IN MAIN.C
void set_lcd(void);
void set_temp();
void display_time();
u8 GetEntries(void);

// LCD DRIVER
void lcd_init();
void lcd_data(u8);
void lcd_cmd(u8);
void lcd_string(s8*);

// UART DRIVER
void uart_init(u32);
void uart_tx(u8);
u8 uart_rx(void);
void uart_string_tx(s8*);
s8* uart_string_rx();
s8* uart_pass_rx();
void uart_ReadTerminal(u8*, u8);

// I2C DRIVER
void i2c_start(void);
void i2c_stop(void);
void i2c_write(u8);
u8 i2c_read(void);
bit i2c_ack(void);
void i2c_noack(void);
bit CheckDevice(u8);
void i2c_detect(void);

// I2C BYTE FRAMES
void i2c_byte_write(u8, u8, u8);
u8 i2c_byte_read(u8, u8);

// DS1621 TEMPERATURE SENSOR
void ds1621_init();
s8 ds1621_read();

// MCP3204 ADC
u16 read_adc(bit,bit);

// EXTERNAL INTERRUPT
void en_ext_interrupt(void);
void Read_EEPROM(void);

// AT24C512 EEPROM DRIVER
void i2c_eeprom_byte_write(u8, u8, u8);
u8 i2c_eeprom_byte_read(u8, u8);

// MAIN 8051_RTWMS.C
void Write_EEPROM(void);