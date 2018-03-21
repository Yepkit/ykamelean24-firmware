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

#ifndef _GPIO_H_
#define _GPIO_H_


#include <xc.h>


// Pin <-> TRISx mapping
#define RB15_TRIS    TRISBbits.TRISB15
#define RB14_TRIS    TRISBbits.TRISB14
#define RB13_TRIS    TRISBbits.TRISB13
#define RB3_TRIS     TRISBbits.TRISB3
#define RA1_TRIS     TRISAbits.TRISA1
#define RB9_TRIS     TRISBbits.TRISB9
#define RB8_TRIS     TRISBbits.TRISB8
#define RB7_TRIS     TRISBbits.TRISB7
#define RB4_TRIS     TRISBbits.TRISB4
#define RB1_TRIS     TRISBbits.TRISB1
#define RA0_TRIS     TRISAbits.TRISA0
#define RA2_TRIS     TRISAbits.TRISA2
#define RA3_TRIS     TRISAbits.TRISA3
#define RA4_TRIS     TRISAbits.TRISA4
#define RB2_TRIS     TRISBbits.TRISB2


// Pin <-> PORTx mapping
#define RB15_PORT    PORTBbits.RB15
#define RB14_PORT    PORTBbits.RB14
#define RB13_PORT    PORTBbits.RB13
#define RB3_PORT     PORTBbits.RB3
#define RA1_PORT     PORTAbits.RA1
#define RB9_PORT     PORTBbits.RB9
#define RB8_PORT     PORTBbits.RB8
#define RB7_PORT     PORTBbits.RB7
#define RB4_PORT     PORTBbits.RB4
#define RB1_PORT     PORTBbits.RB1
#define RA0_PORT     PORTAbits.RA0
#define RA2_PORT     PORTAbits.RA2
#define RA3_PORT     PORTAbits.RA3
#define RA4_PORT     PORTAbits.RA4
#define RB2_PORT     PORTBbits.RB2


// Pin <-> ANSx mapping
#define RB15_ANS    ANSBbits.ANSB15
#define RB14_ANS    ANSBbits.ANSB14
#define RB13_ANS    ANSBbits.ANSB13
#define RB3_ANS     ANSBbits.ANSB3
#define RA1_ANS     ANSAbits.ANSA1
#define RB9_ANS     ANSBbits.ANSB9
#define RB8_ANS     ANSBbits.ANSB8
#define RB7_ANS     ANSBbits.ANSB7
#define RB4_ANS     ANSBbits.ANSB4
#define RB1_ANS     ANSBbits.ANSB1
#define RA0_ANS     ANSAbits.ANSA0
#define RA2_ANS     ANSAbits.ANSA2
#define RA3_ANS     ANSAbits.ANSA3
//#define RA4_ANS     ANSAbits.ANSA4
#define RB2_ANS     ANSBbits.ANSB2



void gpio_write(unsigned char pin_index, unsigned char value);

unsigned char gpio_read(unsigned char pin_index);



#endif

