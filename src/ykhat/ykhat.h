/** \file ykhat.h */
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
#ifndef DEFINED_YKHAT_H
#define DEFINED_YKHAT_H

/**
 * Get temperature in Celsius unit.
 *
 * @param addr YKHaT board I2C slave device address lsb
 * (lest significant bit). The YKHaT supports selection of one of two
 * I2C 7bit addresses. The diference between these two addresses is just these
 * lsb (0 or 1). Because of this we just need to pass to this function the 0 
 * or 1 value.
 * 
 * @return integer value with the temperature in Celsius.
 * 
 */
int ykhat_get_tempC(char addr);

/**
 * Get temperature in Fahrenheit unit.
 *
 * @param addr YKHaT board I2C slave device address lsb
 * (lest significant bit). The YKHaT supports selection of one of two
 * I2C 7bit addresses. The diference between these two addresses is just these
 * lsb (0 or 1). Because of this we just need to pass to this function the 0 
 * or 1 value.
 * 
 * @return integer value with the temperature in Fahrenheit.
 * 
 */
int ykhat_get_tempF(char addr);

/**
 * Get humidity level in %RH unit.
 *
 * @param addr YKHaT board I2C slave device address lsb
 * (lest significant bit). The YKHaT supports selection of one of two
 * I2C 7bit addresses. The diference between these two addresses is just these
 * lsb (0 or 1). Because of this we just need to pass to this function the 0 
 * or 1 value.
 * 
 * @return integer value with the humidity level in %RH unit.
 * 
 */
int ykhat_get_hum(char addr);

#endif
