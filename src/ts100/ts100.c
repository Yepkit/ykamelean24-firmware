/* \file */
/* 
 * Copyright 2018 Yepkit Lda (www.yepkit.com)
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "ts100.h"
#include <math.h>

#define TS100_SDI     PORTBbits.RB4
#define TS100_SCKOUT  LATBbits.LATB3
#define TS100_CS      PORTAbits.RA0


static double RA = 6800;			//default value.
						//ts100_calibrate should be run
						//to calibrate this value.

/**
 * Calculates RTD resistance based on the sensor reading 22 digital output.
 * 
 * @param code 		22 bit sensor reading. This value is the TS100 ADC output.
 * 
 * @return RTD resistance value in Ohm.
 */
static double calc_rt(double code);

/**
 * Calculates the temperature based on the RTD resistance using the formulas defined in DIN EN 60751.
 * 
 * @param rt	RTD resistance in Ohm.
 * 
 * @return Temperature in Celsius degrees (ºC).
 */
static double calc_temp(double rt);

/**
 * Fetches a reading from the TS100 board.
 */
unsigned long ts100_get_sensor_reading(void);


/*!
 * Pin Mapping:
 *	* RB1 -> SDO
 *	* RB4 -> SDI
 *	* RB7 -> SCK
 */
void ts100_spi_enable(void)
{
	//Unlock PPS Registers
	asm volatile	("MOV   #OSCCON, W1     \n"
			"MOV   #0x46, W2       \n"
			"MOV   #0x57, W3       \n"
			"MOV.b W2, [W1]        \n"
			"MOV.b W3, [W1]        \n"
			"BCLR  OSCCON, #6");

	RPINR20bits.SDI1R = 4;	//Assign SDI1 to RB4(RPI4)
	RPOR3bits.RP7R = 8;	//Assign SCK1OUT to RB7(RP7)
	RPOR0bits.RP1R = 7;	//Assign SDO to RB1(RP1)
	//RPOR2bits.RP5R = 9;	//Assign SSO1 (Slave Chip Select) to RA0(RP5)
    
    
	//Lock PPS Registers
	asm volatile	("MOV   #OSCCON, W1     \n"
			"MOV   #0x46, W2       \n"
			"MOV   #0x57, W3       \n"
			"MOV.b W2, [W1]        \n"
			"MOV.b W3, [W1]        \n"
			"BSET  OSCCON, #6");
    
	IEC3bits.SPI1RXIE = 0;		//Disable SPI1 interrupts
	SPI1CON1Lbits.SPIEN = 0;	//Stop and Reset SPI module
	SPI1CON1Lbits.ENHBUF = 0;	//Set standard buffer mode
	SPI1BRGL = 1;			//Define baud rate
	SPI1STATLbits.SPIROV = 0;	//Clear SPI1 Receive Overflow bit
	SPI1CON1Lbits.MSTEN = 1;	//Set Master Mode
	SPI1CON2Lbits.WLENGTH = 0b11000;	//Set the Word Length to 25 bits
	SPI1CON1Lbits.CKP = 1;		//Configure clock to Idle in High Level
	SPI1CON1Lbits.CKE = 0;		//Transmission in falling edge of the clock
	SPI1CON1Hbits.MSSEN = 0;	//Slave chip select by I/O pin
	SPI1CON1Lbits.DISSDO = 1;	//Disable SDO (Just receives)
	SPI1CON1Lbits.SMP = 0;		//Data sample at the midle of clock period (rising edge in this case)
	SPI1CON1Lbits.SPIEN = 1;	//Enable SPI operation
}

unsigned long ts100_get_sensor_raw_reading(void)
{
	unsigned long received_val = 0;
	
	TS100_CS = 0;	//Ensure MCP3551 chip is selected to start conversion
	
	while (TS100_SDI == 1)
		;
	// Write dummy data start reception
	SPI1BUFL = 1;
	SPI1BUFH = 1;
	while(!SPI1STATLbits.SPIRBF)
		;			//Wait for data reception
	received_val = SPI1BUFH & 0b0000000000111111;
	received_val = received_val << 16;
	received_val = received_val + SPI1BUFL;
    
	TS100_CS = 1;			//Disable MCP3551 chip

	return received_val;
}

double ts100_get_temperature(void)
{
	double rt;
	unsigned long reading = 0;

	reading = ts100_get_sensor_raw_reading();	//Get sensor reading
	rt = calc_rt((double) reading);	//Calculate RTD resistance
	return calc_temp(rt);
}


static double calc_rt(double code)
{
	double rt;

	rt = RA * (code / (2097152 - code));	//Calculate Rt
	return rt;
}


static double calc_temp(double rt) 
{
	double a = 0.0039083, b = 0.0000005775;
	
	return (sqrt(a*a - 4*b*(1 - (rt / 100))) - a) / (2*b);
}


void calibrate_sensor(void)
{
	unsigned long reading = 0;

	reading = ts100_get_sensor_raw_reading();
	
	RA = 100 / (reading / (2097152 - reading));
}



double get_calibration_val(void)
{
	return RA;
}


void set_calibration_val(double value)
{
	RA = value;
}