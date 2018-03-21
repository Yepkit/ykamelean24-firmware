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

#include "gpio.h"



void gpio_write(unsigned char pin_index, unsigned char value)
{

	switch (pin_index) {
        case 1:  //RB15
		RB15_ANS = 0;
		RB15_TRIS = 0;
		RB15_PORT = value;
		break;
        case 2:  //RB14
		RB14_ANS = 0;
		RB14_TRIS = 0;
		RB14_PORT = value;
		break;
        case 3:  //RB13
		RB13_ANS = 0;
		RB13_TRIS = 0;
		RB13_PORT = value;
		break;
        case 4:  //RB3
		RB3_ANS = 0;
		RB3_TRIS = 0;
		RB3_PORT = value;
		break;
        case 5:  //RA1
		RA1_ANS = 0;
		RA1_TRIS = 0;
		RA1_PORT = value;
		break;
        case 6:  //RB9
		RB9_ANS = 0;
		RB9_TRIS = 0;
		RB9_PORT = value;
		break;
        case 7:  //RB8
		// RB8_ANS = 0;
		RB8_TRIS = 0;
		RB8_PORT = value;
		break;
        case 8:  //RB7
		//RB7_ANS = 0;
		RB7_TRIS = 0;
		RB7_PORT = value;
		break;
        case 9:  //RB4
		//RB4_ANS = 0;
		RB4_TRIS = 0;
		RB4_PORT = value;
		break;
        case 10:  //RB1
		RB1_ANS = 0;
		RB1_TRIS = 0;
		RB1_PORT = value;
		break;
        case 11:  //RA0
		RA0_ANS = 0;
		RA0_TRIS = 0;
		RA0_PORT = value;
		break;
        case 12:  //RA2
		RA2_ANS = 0;
		RA2_TRIS = 0;
		RA2_PORT = value;
		break;
        case 13:  //RA3
		RA3_ANS = 0;
		RA3_TRIS = 0;
		RA3_PORT = value;
		break;
        case 14:  //RA4
		// RA4_ANS = 0;
		RA4_TRIS = 0;
		RA4_PORT = value;
		break;
        case 15: //RB2
		RB2_ANS = 0;
		RB2_TRIS = 0;
		RB2_PORT = value;
		break;
        default: 
		break;
	}
}




unsigned char gpio_read(unsigned char pin_index) {

    unsigned char value=0;

    switch(pin_index) {

        case 1:  //RB15
            RB15_ANS = 0;
            RB15_TRIS = 1;
            value = RB15_PORT;
            break;

        case 2:  //RB14
            RB14_ANS = 0;
            RB14_TRIS = 1;
            value = RB14_PORT;
            break;

        case 3:  //RB13
            RB13_ANS = 0;
            RB13_TRIS = 1;
            value = RB13_PORT;
            break;

        case 4:  //RB3
            RB3_ANS = 0;
            RB3_TRIS = 1;
            value = RB3_PORT;
            break;

        case 5:  //RA1
            RA1_ANS = 0;
            RA1_TRIS = 1;
            value = RA1_PORT;
            break;

        case 6:  //RB9
            RB9_ANS = 0;
            RB9_TRIS = 1;
            value = RB9_PORT;
            break;

        case 7:  //RB8
           // RB8_ANS = 0;
            RB8_TRIS = 1;
            value = RB8_PORT;
            break;

        case 8:  //RB7
           // RB7_ANS = 0;
            RB7_TRIS = 1;
            value = RB7_PORT;
            break;

        case 9:  //RB4
            //RB4_ANS = 0;
            RB4_TRIS = 1;
            value = RB4_PORT;
            break;

        case 10:  //RB1
            RB1_ANS = 0;
            RB1_TRIS = 1;
            value = RB1_PORT;
            break;

        case 11:  //RA0
            RA0_ANS = 0;
            RA0_TRIS = 1;
            value = RA0_PORT;
            break;

        case 12:  //RA2
            RA2_ANS = 0;
            RA2_TRIS = 1;
            value = RA2_PORT;
            break;

        case 13:  //RA3
            RA3_ANS = 0;
            RA3_TRIS = 1;
            value = RA3_PORT;
            break;

        case 14:  //RA4
            //RA4_ANS = 0;
            ODCAbits.ODA4 = 0;
            RA4_TRIS = 1;
            value = RA4_PORT;
            //value = LATAbits.LATA4;
            break;

        case 15: //RB2
            RB2_ANS = 0;
            RB2_TRIS = 1;
            value = RB2_PORT;
            break;
        
        default: 
            break;
    }

    return value;

}




