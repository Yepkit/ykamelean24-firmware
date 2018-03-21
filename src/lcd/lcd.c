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
 
#include "lcd.h"


static void delay_ms(unsigned int ms)
{
	unsigned int i, j = 0;
	for (i = 0; i < ms; i++)
		do
		    j++;
		while (j < 4000);
	return;
}

void lcd_init(void) 
{
	// board hardware configuration for pins used to connect the LCD
	CVRCONbits.CVREN = 0;
	CVRCONbits.CVROE = 0;
	REFOCONLbits.ROEN = 0;
	REFOCONLbits.ROOUT = 0;

	// configure all I/Os used in the LDC interface as Digital outputs 
	ANSAbits.ANSA1 = 0; 
	ANSBbits.ANSB2 = 0;
	ANSBbits.ANSB3 = 0;
	ANSBbits.ANSB13 = 0;
	ANSBbits.ANSB14 = 0;
	ANSBbits.ANSB15 = 0;
	
	TRISAbits.TRISA1 = 0;
	TRISBbits.TRISB2 = 0;
	TRISBbits.TRISB3 = 0;
	TRISBbits.TRISB13 = 0;
	TRISBbits.TRISB14 = 0;
	TRISBbits.TRISB15 = 0;
    
	// LCD reset for 4 bit operation
	delay_ms(20);
	LCD_RS = 0;
	LCD_E = 1;
	LCD_DB7 = 0;
	LCD_DB6 = 0;
	LCD_DB5 = 1;
	LCD_DB4 = 1;
	LCD_E = 0;
	
	delay_ms(10);
	LCD_RS = 0;
	LCD_E = 1;
	LCD_DB7 = 0;
	LCD_DB6 = 0;
	LCD_DB5 = 1;
	LCD_DB4 = 1;
	LCD_E = 0;
	
	delay_ms(1);
	LCD_RS = 0;
	LCD_E = 1;
	LCD_DB7 = 0;
	LCD_DB6 = 0;
	LCD_DB5 = 1;
	LCD_DB4 = 1;
	LCD_E = 0;
	
	delay_ms(1);
	LCD_RS = 0;
	LCD_E = 1;
	LCD_DB7 = 0;
	LCD_DB6 = 0;
	LCD_DB5 = 1;
	LCD_DB4 = 0;
	LCD_E = 0;
	delay_ms(1);

	//function set
	lcd_cmd(0x28);		// 4-bit mode - 2 line - 5x7 font. 
	lcd_cmd(0x0C);		// Display no cursor - no blink.
	lcd_cmd(0x06);		// Automatic Increment - No Display shift.
	lcd_cmd(0x80);		// Address DDRAM with 0 offset 80h.
}

void lcd_cmd(unsigned char cmd)
{	
	LCD_RS = 0;
	// first send MSb 4 bits
	LCD_E = 1;
	LCD_DB7 = cmd >> 7 & 0x01;
	LCD_DB6 = cmd >> 6 & 0x01;
	LCD_DB5 = cmd >> 5 & 0x01;
	LCD_DB4 = cmd >> 4 & 0x01;
	LCD_E = 0;
	// next send LSb 4 bits
	LCD_E = 1;
	LCD_DB7 = cmd >> 3 & 0x01;
	LCD_DB6 = cmd >> 2 & 0x01;
	LCD_DB5 = cmd >> 1 & 0x01;
	LCD_DB4 = cmd & 0x01;
	LCD_E = 0;
	
	delay_ms(400);
}

void lcd_data(unsigned char data)
{	
	LCD_RS = 1;
	// first send MSb 4 bits
	LCD_E = 1;
	LCD_DB7 = data >> 7 & 0x01;
	LCD_DB6 = data >> 6 & 0x01;
	LCD_DB5 = data >> 5 & 0x01;
	LCD_DB4 = data >> 4 & 0x01;
	LCD_E = 0;
	// next send LSb 4 bits
	LCD_E = 1;
	LCD_DB7 = data >> 3 & 0x01;
	LCD_DB6 = data >> 2 & 0x01;
	LCD_DB5 = data >> 1 & 0x01;
	LCD_DB4 = data & 0x01;
	LCD_E = 0;
	
	delay_ms(400);
}


 
