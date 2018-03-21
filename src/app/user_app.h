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

#ifndef USER_APP_H
#define	USER_APP_H

#include <xc.h>

/*!
 * User application front-controller functions calls should be placed here.
 * 
 * This function is called in every cicle of the firmware main loop.
 */
void user_app(void);

/*!
 * User interrupt handlers should be placed here.
 * 
 * Care should be taken as some interrupts are already being used by the
 * baseline firmware code. Please refer to documentation for reference.
 */
void user_interrupts(void);

/*!
 * User USB In/Out message handlers should be placed here. 
 * 
 * \param usb_in_buffer         64 byte buffer containing the received USB message
 * \param usb_out_buffer        64 byte buffer containing the message to be
 *                              transmitted back to the USB host.
 */
void user_usb_io(unsigned char *usb_in_buffer, unsigned char *usb_out_buffer);



#endif

