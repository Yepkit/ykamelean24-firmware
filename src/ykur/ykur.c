/*! \file */

#include <xc.h>
#include "ykur.h"


void ykur_i2c_idle(void);

/*!
 * Ensures that all is properly configured and initialized
 * for the I2C communication with YKUR boards I2C control
 * interface.
 * 
 * \param brg baud rate factor
 */          
unsigned char ykur_i2cInit(unsigned int brg);



unsigned char ykur_i2cInit(unsigned int brg)
{
	I2C1CONLbits.I2CEN = 0;     // ensure that I2C is disabled.

	/*! Baudrate calculation
	 * -----------------------
	 */
	//! I2CxBRG = ((1/FSCL - PGDx)*FCY/2)-2
	//!  note: PGDx = Delay = Pulse Gobbler Delay
	//! example taking FCY = 16000000, FSCL = 400kHz, PGDx = 120ns:
	//!   ((1/400000-120/1000000000)*(16000000/2))-2 = 17
	//! note: based on FCY = FOSC/2, doze mode and PLL disabled
	//! the SCL divider uses 9 bits
	I2C1BRG = (brg > 511 ? 511 : brg);

	I2C1CONLbits.A10M = 0;		//7-bit slave address
	I2C1CONLbits.DISSLW = 1;	//enable slew rate control for high speed
	I2C1STAT = 0;			// reset stats
	I2C1CONLbits.I2CEN = 1;		// Enable I2C module

	return 0;
}

char ykur_i2cGetResponse(char *cmd_buffer, char address) 
{
	//! ToDo
	return 0;
}

char ykur_i2cSendCommand(unsigned char cmd_buffer, char num_bytes, unsigned char address)
{    
	char i;
	
	ykur_i2cInit(100);
	
	ykur_i2c_idle();
	I2C1CONLbits.SEN = 1;	//initiate start event		
	do 
	    Nop();
	while (I2C1CONLbits.SEN);

	ykur_i2c_idle();
	I2C1TRNbits.I2CTXDATA = (address << 1) & 0b11111110;    //ykur i2c address
	while (I2C1STATbits.TRSTAT == 1)
		;				// Wait for transmission
	if (I2C1STATbits.ACKSTAT == 1)
		return 1;     

	for (i = 0; i < num_bytes; i++) {
		ykur_i2c_idle();
		I2C1TRNbits.I2CTXDATA = cmd_buffer;		//data byte
		while (I2C1STATbits.TRSTAT == 1)
			;
		if (I2C1STATbits.ACKSTAT == 1)
			return 2;     
	}

	ykur_i2c_idle();
	I2C1CONLbits.PEN = 1;	//Generate STOP condition
	do 
	    Nop();
	while (I2C1CONLbits.PEN);
	return 0;
}







void ykur_i2c_idle(void) {
    do
        Nop();
    while (I2C1CONL & 0x1f);

    return;
}





