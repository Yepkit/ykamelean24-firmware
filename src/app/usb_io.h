/*! \file
 * 
 * Handles the USB YKAMELEAN24 control interface. 
 * All commands are parsed and the respective specific task/handler
 * functions are called.
 * 
 */

/*
Copyright 2017 Yepkit Lda (www.yepkit.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*******************************************************************************/


#ifndef _USB_IO_H_
#define _USB_IO_H_

#include "app.h"

/*!
 * Parses the received USB message and call the specific handler functions.
 * 
 */
void app_process_usb_io(unsigned char *ReceivedDataBuffer, unsigned char *ToSendDataBuffer); 


#endif

