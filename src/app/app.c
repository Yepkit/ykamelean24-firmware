/*! \file */
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


#include "app.h"


/*!
 * YKEMB module USB command parser.
 */
char app_ykemb(unsigned char *ReceivedDataBuffer, unsigned char *ToSendDataBuffer)
{
	unsigned char error = 0;

	switch (ReceivedDataBuffer[2]) {
	case 0x01:  //Write command 
		ykemb_i2cInit(20);      //Ensure I2C is properly configured for
					//operation with YKEMB.
					//It is not the most efficient to call
					//this every time a command for YKEMB is 
					//received, but for an example application
					//it is the safest approach.
		error = ykemb_byteWrite(ReceivedDataBuffer[6], ReceivedDataBuffer[3], &ReceivedDataBuffer[4]);
		ToSendDataBuffer[0] = 0x10;
		ToSendDataBuffer[1] = 0x02;
		ToSendDataBuffer[2] = ReceivedDataBuffer[2];
		ToSendDataBuffer[3] = ReceivedDataBuffer[3];
		ToSendDataBuffer[4] = ReceivedDataBuffer[4];
		ToSendDataBuffer[5] = ReceivedDataBuffer[5];
		ToSendDataBuffer[6] = ReceivedDataBuffer[6];
		ToSendDataBuffer[7] = error;
		break;
	case 0x02:  //Read command
		ykemb_i2cInit(20);      //Ensure I2C is properly configured for
					//operation with YKEMB.
					//It is not the most efficient to call
					//this every time a command for YKEMB is 
					//received, but for an example application
					//it is the safest approach.
		ToSendDataBuffer[6] = 0;    //reset value
		error = ykemb_i2cSelByteRead(ReceivedDataBuffer[3], &ReceivedDataBuffer[4], &ToSendDataBuffer[6]);
		ToSendDataBuffer[0] = 0x10;
		ToSendDataBuffer[1] = 0x02;
		ToSendDataBuffer[2] = ReceivedDataBuffer[2];
		ToSendDataBuffer[3] = ReceivedDataBuffer[3];
		ToSendDataBuffer[4] = ReceivedDataBuffer[4];
		ToSendDataBuffer[5] = ReceivedDataBuffer[5];
		ToSendDataBuffer[7] = error;
		break;
	default: 
		break;
	}

	return error;
}


/*!
 * GPIO module USB command parser.
 */
char app_gpio(unsigned char *ReceivedDataBuffer, unsigned char *ToSendDataBuffer)
{
	switch (ReceivedDataBuffer[2]) {

	case 0x01:  //Write command 
		gpio_write(ReceivedDataBuffer[3], ReceivedDataBuffer[4]);
		ToSendDataBuffer[0] = 0x01;
		ToSendDataBuffer[1] = 0x01;
		ToSendDataBuffer[2] = 0x01;
		ToSendDataBuffer[3] = ReceivedDataBuffer[3];
		ToSendDataBuffer[4] = ReceivedDataBuffer[4];
		break;
	case 0x02:  //Read command
		ToSendDataBuffer[0] = 0x01;
		ToSendDataBuffer[1] = 0x01;
		ToSendDataBuffer[2] = 0x02;
		ToSendDataBuffer[3] = ReceivedDataBuffer[3];
		ToSendDataBuffer[4] = gpio_read(ReceivedDataBuffer[3]);
		break;
	default: 
		break;
	}

	return 0;
}

/*!
 * YKUR module USB command parser.
 * 
 * The command should have the following structure:
 * 
 * byte 1 | byte 2 | byte 3 
 * -------|--------|-------
 * 0x11   | action | status
 * 
 * Where action can be the following:
 * 
 * action to be performed  |   byte 2 value in hexadecimal
 * ---------------------|---------------------------------
 * Switch ON relay      | 0x01
 * Switch OFF relay     | 0x02
 * Switch ON port 1     | 0x03
 * Switch ON port 2     | 0x04
 * Switch ON port 3     | 0x05
 * Switch ON port 4     | 0x06
 * Switch OFF port 1    | 0x07
 * Switch OFF port 2    | 0x08
 * Switch OFF port 3    | 0x09
 * Switch OFF port 4    | 0x0A
 * Switch ON all ports  | 0x0B
 * Switch OFF all ports | 0x0C
 * Switch ON all ports and relay  | 0x0D
 * Switch OFF all ports and relay  | 0x0E
 * Get relay switching state | 0x0F
 * Get port 1 switching state | 0x1F
 * Get port 2 switching state | 0x2F
 * Get port 3 switching state | 0x3F
 * Get port 4 switching state | 0x4F
 * 
 * The Ykamelean24 will send the following response message after executing the command.
 * 
 * byte 1 | byte 2 | byte 3 
 * -------|--------|-------
 * 0x11   | action | status
 * 
 * Where:
 * 
 * status	| descritpion
 * -------------|-------------
 * 0		| Command executed with success
 * 1		| Error sending YKUR slave address through I2C
 * 2		| Error sending command byte through I2C
 * 	
 * 
 * \param ReceivedDataBuffer	Buffer for data received from USB host (command).
 * \param ToSendDataBuffer	Buffer for data to be sent to USB host (response).
 * 
 * \return 0 Ok
 * \return 1 Error in I2C transmission
 */
char app_ykur(unsigned char *ReceivedDataBuffer, unsigned char *ToSendDataBuffer)
{
	ToSendDataBuffer[0] = ReceivedDataBuffer[0];
	ToSendDataBuffer[1] = ReceivedDataBuffer[1];
	ToSendDataBuffer[2] = ykur_i2cSendCommand(ReceivedDataBuffer[1], 1, 0b01010001);
	return 0;
}

/*
 * 
 */
char app_ts100()
{
	return 0;
}

/*
 * 
 */
char app_ykhat(unsigned char *ReceivedDataBuffer, unsigned char *ToSendDataBuffer) 
{
    int tempC, tempF, hum;
    
    unsigned char valMSB=0, valLSB=0;


    switch(ReceivedDataBuffer[2]) {

        case 0x01: //Get temperature in ºC
            tempC = ykhat_get_tempC(ReceivedDataBuffer[3]);
            valMSB = (tempC >> 8) & 0x00FF;
            valLSB = tempC & 0x00FF;
            ToSendDataBuffer[0] = 0x12;
            ToSendDataBuffer[1] = 0x02;
            ToSendDataBuffer[2] = ReceivedDataBuffer[2];
            ToSendDataBuffer[3] = ReceivedDataBuffer[3];
            ToSendDataBuffer[4] = valMSB;
            ToSendDataBuffer[5] = valLSB;

            break;

        case 0x02: //Get temperature in ÂºF
            tempF = ykhat_get_tempF(ReceivedDataBuffer[3]);
            valMSB = (tempF >> 8) & 0x00FF;
            valLSB = tempF & 0x00FF;
            ToSendDataBuffer[0] = 0x12;
            ToSendDataBuffer[1] = 0x02;
            ToSendDataBuffer[2] = ReceivedDataBuffer[2];
            ToSendDataBuffer[3] = ReceivedDataBuffer[3];
            ToSendDataBuffer[4] = valMSB;
            ToSendDataBuffer[5] = valLSB;

            break;

        case 0x03: //Get humidity in %RH
            hum = ykhat_get_hum(ReceivedDataBuffer[3]);
            valMSB = (hum >> 8) & 0x00FF;
            valLSB = hum & 0x00FF;
            ToSendDataBuffer[0] = 0x12;
            ToSendDataBuffer[1] = 0x02;
            ToSendDataBuffer[2] = ReceivedDataBuffer[2];
            ToSendDataBuffer[3] = ReceivedDataBuffer[3];
            ToSendDataBuffer[4] = valMSB;
            ToSendDataBuffer[5] = valLSB;

            break;

        case 0x11:  //Start sensor reading
            ykhat_start_sensor_reading(ReceivedDataBuffer[3]);
            ToSendDataBuffer[0] = 0x12;
            ToSendDataBuffer[1] = 0x02;
            ToSendDataBuffer[2] = ReceivedDataBuffer[2];
            ToSendDataBuffer[3] = ReceivedDataBuffer[3];

            break;

        default:
            break;
    }

    return 0;
}




/*
 * Function:
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Precedences:
 *
 *****************************************************************/

char app_lcd() {

    return 0;
}



/*
 * Function:
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Precedences:
 *
 *****************************************************************/

char app_i2c() {

    return 0;
}


