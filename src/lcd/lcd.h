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

#ifndef LCD_H
#define LCD_H

#include <xc.h>
#include <gpio.h>

/*!
 * LCD Pins to Ykamelean24 board pins mapping.
 * 
 *      * LCD_E   ->      RA1
 *      * LCD_RS  ->      RB7
 *      * LCD_DB4 ->      RB3
 *      * LCD_DB5 ->      RB13
 *      * LCD_DB6 ->      RB14
 *      * LCD_DB7 ->      RB15
 */ 
#define LCD_E           LATAbits.LATA1
#define LCD_RS          LATBbits.LATB2
#define LCD_DB4         LATBbits.LATB3
#define LCD_DB5         LATBbits.LATB13
#define LCD_DB6         LATBbits.LATB14
#define LCD_DB7         LATBbits.LATB15

/*!
 * LCD initialization function.
 * 
 * By calling this function the LCD is reset and initializated to 4 bit
 * interface.
 */
void lcd_init(void);

/*!
 * LCD command function.
 * 
 * Sends a command to the LCD.
 * 
 * \param cmd   byte containing the command value (opcode) as defined in the
 * LCD datasheet.
 */
void lcd_cmd(unsigned char cmd);

/*!
 * LCD data function.
 * 
 * Sends data to LCD.
 * 
 * \param data  data byte to be sent to LCD.
 */
void lcd_data(unsigned char data);



#endif
