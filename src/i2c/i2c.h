/****************************************************************************
 *         Summary: I2C sync communication sample code
 * Processor/Board: PIC24FJ128GB202/PYK24 dev board
 *       Developer: ckuesters@yepkit.com
*****************************************************************************/

#include <stdbool.h> // for bool

// I2C consts

// you need to provide the FCY value
#define FCY                 16000000ul

// max sync operation wait = 22*12+(192-22)*12000us = ~504ms
#define I2C_TIMEUP_COUNTMAX  64
#define I2C_TIMEUP_COUNTFAST 22
#define I2C_TIMEUP_WAITFAST  12
#define I2C_TIMEUP_WAITSLOW  12000

// the functions with return values will return 0 in case of success
// I2C module 1 functions, self explanatory names and arguments

void i2c1_init(unsigned int brg);

void i2c1_shut(void);

unsigned char i2c1_reset_bus(void);

bool i2c1_slave_alive(unsigned char slvaddr);

unsigned char i2c1_receive_next(bool lastbyte, unsigned char *byte);

unsigned char i2c1_receive_first(unsigned char slvaddr, unsigned char regaddr, bool regexist, bool lastbyte, unsigned char *byte);

unsigned char i2c1_read_register_byte(unsigned char slvaddr, unsigned char regaddr, unsigned char *byte);

unsigned char i2c1_read_register_word(unsigned char slvaddr, unsigned char regaddr, unsigned int *word);

unsigned char i2c1_read_byte(unsigned char slvaddr, unsigned char *byte);

unsigned char i2c1_read_word(unsigned char slvaddr, unsigned int *word);

unsigned char i2c1_read_data(unsigned char slvaddr, unsigned char *data, unsigned int len);

unsigned char i2c1_send_next(bool lastbyte, unsigned char byte);

unsigned char i2c1_send_first(unsigned char slvaddr, unsigned char regaddr, bool regexist, bool lastbyte, unsigned char byte);

unsigned char i2c1_write_register_byte(unsigned char slvaddr, unsigned char regaddr, unsigned char byte);

unsigned char i2c1_write_register_word(unsigned char slvaddr, unsigned char regaddr, unsigned int word);

unsigned char i2c1_write_byte(unsigned char slvaddr, unsigned char byte);

unsigned char i2c1_write_word(unsigned char slvaddr, unsigned int word);

unsigned char i2c1_write_str(unsigned char slvaddr, char *data);

unsigned char i2c1_write_data(unsigned char slvaddr, unsigned char *data, unsigned int len);


// I2C module 2 functions, self explanatory names and arguments

void i2c2_init(unsigned int brg);

void i2c2_shut(void);

unsigned char i2c2_reset_bus(void);

bool i2c2_slave_alive(unsigned char slvaddr);

unsigned char i2c2_receive_next(bool lastbyte, unsigned char *byte);

unsigned char i2c2_receive_first(unsigned char slvaddr, unsigned char regaddr, bool regexist, bool lastbyte, unsigned char *byte);

unsigned char i2c2_read_register_byte(unsigned char slvaddr, unsigned char regaddr, unsigned char *byte);

unsigned char i2c2_read_register_word(unsigned char slvaddr, unsigned char regaddr, unsigned int *word);

unsigned char i2c2_read_byte(unsigned char slvaddr, unsigned char *byte);

unsigned char i2c2_read_word(unsigned char slvaddr, unsigned int *word);

unsigned char i2c2_read_data(unsigned char slvaddr, unsigned char *data, unsigned int len);

unsigned char i2c2_send_next(bool lastbyte, unsigned char byte);

unsigned char i2c2_send_first(unsigned char slvaddr, unsigned char regaddr, bool regexist, bool lastbyte, unsigned char byte);

unsigned char i2c2_write_register_byte(unsigned char slvaddr, unsigned char regaddr, unsigned char byte);

unsigned char i2c2_write_register_word(unsigned char slvaddr, unsigned char regaddr, unsigned int word);

unsigned char i2c2_write_byte(unsigned char slvaddr, unsigned char byte);

unsigned char i2c2_write_word(unsigned char slvaddr, unsigned int word);

unsigned char i2c2_write_str(unsigned char slvaddr, char *data);

unsigned char i2c2_write_data(unsigned char slvaddr, unsigned char *data, unsigned int len);

