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


#ifndef TS100_H
#define TS100_H

#include <xc.h>

#define TS100_SDI     PORTBbits.RB4
#define TS100_SCKOUT  LATBbits.LATB3
#define TS100_CS      PORTAbits.RA0


/*!
 * SPI configuration and initialization for use with TS100 board.
 */
void ts100_spi_enable(void);

/*!
 * Fetches a reading from the TS100 board.
 */
unsigned long ts100_get_sensor_reading(void);

/*!
 * Get temperature value in Celsius.
 */
double ts100_get_temperature(void);

/*!
 * Get calibration value.
 */
double get_calibration_val(void);

#endif



