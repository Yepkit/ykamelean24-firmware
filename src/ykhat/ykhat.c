/** \file ykhat.c */
/*
Copyright 2018 Yepkit Lda (www.yepkit.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <xc.h>
#include "ykhat.h"

void ykhat_i2c_idle(void);
void ykhat_start_sensor_reading(char addr);
char ykhat_get_sensor_reading(char addr, char *buffer);


int ykhat_get_tempC(char addr)
{
	int temperature = 0;
	long st = 0;
	char buffer[6];
	
	ykhat_get_sensor_reading(addr, buffer);
	
	//---------------------------------
	//Convert to ºC unit
	//---------------------------------
	st = buffer[0];
	st = (st << 8) + buffer[1];
	temperature = ((175 * st) / 65535) - 45;
	return temperature;
}

int ykhat_get_tempF(char addr)
{
	int temperature=0;
	long st=0;
	char buffer[6];

	ykhat_get_sensor_reading(addr, buffer);
	
	//---------------------------------
	//Convert to ºC unit
	//---------------------------------
	st = buffer[0];
	st = (st << 8) + buffer[1];
	temperature = ((315 * st) / 65535) - 49;	
	return temperature;
}

int ykhat_get_hum(char addr)
{
	int humidity=0;
	long srh=0;
	char buffer[6];

	ykhat_get_sensor_reading(addr, buffer);

	//---------------------------------
	//Convert to ºC unit
	//---------------------------------
	srh = buffer[3];
	srh = (srh << 8) + buffer[4];
	humidity = (100 * srh) / 65535;
	return humidity;
}

void ykhat_init_i2c(unsigned int brg) 
{
	// ensure I2C is disabled
	I2C1CONLbits.I2CEN = 0;
	// I2CxBRG = ((1/FSCL - PGDx)*FCY/2)-2
	//   note: PGDx = Delay = Pulse Gobbler Delay
	// example taking FCY = 16000000, FSCL = 400kHz, PGDx = 120ns:
	//   ((1/400000-120/1000000000)*(16000000/2))-2 = 17
	// note: based on FCY = FOSC/2, doze mode and PLL disabled
	// the SCL divider uses 9 bits
	I2C1BRG = (brg > 511 ? 511 : brg);
	
	// 7-bit slave address
	I2C1CONLbits.A10M = 0; 
	// enable slew rate control for high speed
	I2C1CONLbits.DISSLW = 1;
	
	// reset stats
	I2C1STAT = 0;
	// Enable I2C module
	I2C1CONLbits.I2CEN = 1;
}


void ykhat_i2c_idle(void)
{
	do
		Nop();
	while (I2C1CONL & 0x1f);
	return;
}

void ykhat_start_sensor_reading(char addr)
{
	//------------------------------------
	//1. Initialize I2C communication
	//------------------------------------
	ykhat_init_i2c(100);

	//------------------------------------
	//2. Read from sensor
	//------------------------------------

	//2.1. Initiate START event
	// ------------------------
	ykhat_i2c_idle();
	I2C1CONLbits.SEN = 1;
	// then wait for completion
	// ToDo: Insert max time condition 
	do 
		Nop();
	while (I2C1CONLbits.SEN);
	
	//2.2. Send the I2C device address byte w/ write bit
	// ------------------------------------------------
	ykhat_i2c_idle();
	if (addr & 0x01)
		I2C1TRNbits.I2CTXDATA = 0b10001010;    
	else
		I2C1TRNbits.I2CTXDATA = 0b10001000;    

	// Wait for and verify an Acknowledge from the slave
	// Wait for transmission
	while (I2C1STATbits.TRSTAT == 1) {};
	// Check ACK
	if (I2C1STATbits.ACKSTAT == 1)
		return;     
	
	//2.3. Send the command bytes
	// ------------------------------------------
	ykhat_i2c_idle();
	// Send MSB command byte
	I2C1TRNbits.I2CTXDATA = 0x24;
	// Wait for and verify an Acknowledge from the slave
	// Wait for transmission
	while (I2C1STATbits.TRSTAT == 1) {};
	// Check ACK
	if (I2C1STATbits.ACKSTAT == 1)
		return;     

	ykhat_i2c_idle();
	// Send LSB command byte
	I2C1TRNbits.I2CTXDATA = 0x00;
	// Wait for and verify an Acknowledge from the slave
	// Wait for transmission
	while (I2C1STATbits.TRSTAT == 1) {};
	// Check ACK
	if (I2C1STATbits.ACKSTAT == 1)
		return;     
	
	//2.4. Generate STOP condition
	// -------------------------- 
	ykhat_i2c_idle();
	// Initiate stop
	I2C1CONLbits.PEN = 1;
	do 
		Nop();
	while (I2C1CONLbits.PEN);

	//2.5. Initiate START event
	// ------------------------
	ykhat_i2c_idle();
	I2C1CONLbits.SEN = 1;
	// then wait for completion
	// ToDo: Insert max time condition 
	do 
		Nop();
	while (I2C1CONLbits.SEN);

	//2.6. Send the I2C device address byte w/ read bit
	//-------------------------------------------------
	ykhat_i2c_idle();
	if (addr & 0x01)
		I2C1TRNbits.I2CTXDATA = 0b10001011;    
	else
		I2C1TRNbits.I2CTXDATA = 0b10001001;    
	// Wait for transmission
	while (I2C1STATbits.TRSTAT == 1) {};
	// Check ACK
	if (I2C1STATbits.ACKSTAT == 1) 
	{
		//2.4. Generate STOP condition
		// -------------------------- 
		ykhat_i2c_idle();
		// Initiate stop
		I2C1CONLbits.PEN = 1;
		do 
			Nop();
		while (I2C1CONLbits.PEN);    
	}

	//Clear master logic
	I2C1CONLbits.ACKEN = 0;
	I2C1CONLbits.RCEN = 0;
	I2C1CONLbits.PEN = 0;
	I2C1CONLbits.RSEN = 0;
	I2C1CONLbits.SEN = 0;
	return;
}

char ykhat_get_sensor_reading(char addr, char *buffer)
{
	//------------------------------------
	//1. Initialize I2C communication
	//------------------------------------
	ykhat_init_i2c(100);

	//------------------------------------
	//2. Read from sensor
	//------------------------------------
	//2.5. Initiate START event
	// ------------------------
	ykhat_i2c_idle();
	I2C1CONLbits.SEN = 1;
	// then wait for completion
	do 
		Nop();
	while (I2C1CONLbits.SEN);

	//2.6. Send the I2C device address byte w/ read bit
	//-------------------------------------------------
	ykhat_i2c_idle();
	if (addr)
		I2C1TRNbits.I2CTXDATA = 0b10001011;    
	else
		I2C1TRNbits.I2CTXDATA = 0b10001001;    
	
	// Wait for transmission
	while (I2C1STATbits.TRSTAT == 1) {};
	// Check ACK
	if (I2C1STATbits.ACKSTAT == 1)
		return -100;     

	//2.7. Enable Master Reception
	// --------------------------
	I2C1CONLbits.RCEN = 1;

	//2.8. Read received bytes
	// -----------------------
	// Read temperature MSB byte
	while (I2C1STATbits.RBF == 0){};
	buffer[0] = I2C1RCVbits.I2CRXDATA;
	//ACK
	ykhat_i2c_idle();
	I2C1CONLbits.ACKDT = 0;
	I2C1CONLbits.ACKEN = 1;
	do 
		Nop();
	while (I2C1CONLbits.ACKEN);

	I2C1CONLbits.RCEN = 1;

	// Read temperature LSB byte
	while (I2C1STATbits.RBF == 0){};
	buffer[1] = I2C1RCVbits.I2CRXDATA;
	//ACK
	ykhat_i2c_idle();
	I2C1CONLbits.ACKDT = 0;
	I2C1CONLbits.ACKEN = 1;
	do 
		Nop();
	while (I2C1CONLbits.ACKEN);

	I2C1CONLbits.RCEN = 1;

	// Read CRC byte
	while (I2C1STATbits.RBF == 0){};
	buffer[2] = I2C1RCVbits.I2CRXDATA;
	//ACK
	ykhat_i2c_idle();
	I2C1CONLbits.ACKDT = 0;
	I2C1CONLbits.ACKEN = 1;
	do 
		Nop();
	while (I2C1CONLbits.ACKEN);

	I2C1CONLbits.RCEN = 1;

	// Read humidity MSB byte
	while (I2C1STATbits.RBF == 0){};
	buffer[3] = I2C1RCVbits.I2CRXDATA;
	//ACK
	ykhat_i2c_idle();
	I2C1CONLbits.ACKDT = 0;
	I2C1CONLbits.ACKEN = 1;
	do 
		Nop();
	while (I2C1CONLbits.ACKEN);

	I2C1CONLbits.RCEN = 1;

	// Read humidity LSB byte
	while (I2C1STATbits.RBF == 0){};
	buffer[4] = I2C1RCVbits.I2CRXDATA;
	//ACK
	ykhat_i2c_idle();
	I2C1CONLbits.ACKDT = 0;
	I2C1CONLbits.ACKEN = 1;
	do 
		Nop();
	while (I2C1CONLbits.ACKEN);

	I2C1CONLbits.RCEN = 1;

	// Read CRC byte
	while (I2C1STATbits.RBF == 0){};
	buffer[5] = I2C1RCVbits.I2CRXDATA;
	
	//NACK
	ykhat_i2c_idle();
	I2C1CONLbits.ACKDT = 1;
	I2C1CONLbits.ACKEN = 1;
	do 
		Nop();
	while (I2C1CONLbits.ACKEN);

	//2.8. STOP
	// --------
	// Initiate stop
	I2C1CONLbits.PEN = 1;
	do 
		Nop();
	while (I2C1CONLbits.PEN);

	//Clear master logic
	I2C1CONLbits.ACKEN = 0;
	I2C1CONLbits.RCEN = 0;
	I2C1CONLbits.PEN = 0;
	I2C1CONLbits.RSEN = 0;
	I2C1CONLbits.SEN = 0;
	return 0;
}







