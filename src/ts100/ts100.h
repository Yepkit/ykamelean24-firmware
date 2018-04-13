/** \file ts100.h */
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


#ifndef DEFINED_TS100_H
#define DEFINED_TS100_H

#include <xc.h>


/**
 * MCU SPI configuration and initialization for use with TS100 board.
 */
void ts100_spi_enable(void);


/*!
 * Fetches a reading from the TS100 board.
 */
unsigned long ts100_get_sensor_raw_reading(void);


/**
 * Get temperature value in Celsius.
 */
double ts100_get_temperature(void);


/*!
 * Performs sensor calibration.
 * 
 * Pre-requisites:
 *	On-board jumper should be set to "CAL" position. 
 *  
 */
void calibrate_sensor(void);


/*!
 * Get calibration value.
 * 
 * Returns the calibration value which was set by a previous calibration routine
 * (call of calibrate_sensor() function).
 * 
 */
double get_calibration_val(void);


/*!
 * Sets calibration value.
 * 
 * Sets the internal variable which contains the calibration value.
 * This function should be used to bypass the calibrate_sensor() routine,
 * for example when a previous calibration value was stored in a persistent
 * memory and should be reused.
 * 
 */
void set_calibration_val(double value);




#endif



