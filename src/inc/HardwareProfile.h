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
*/


#ifndef HARDWAREPROFILE_H
#define HARDWAREPROFILE_H

    /************************************************************************
     *                                                                      *
     *              USB stack hardware selection options                    *
     *                                                                      *
     ************************************************************************/
     /**
      * This section is the set of definitions required by the MCHPFSUSB
      * framework.  These definitions tell the firmware what mode it is
      * running in, and where it can find the results to some information
      * that the stack needs.
      **/

    //#define USE_SELF_POWER_SENSE_IO
    //#define tris_self_power     TRISCbits.TRISC2    // Input
    #define self_power          0   // Bus powered device

    //#define USE_USB_BUS_SENSE_IO
    //#define tris_usb_bus_sense  TRISCbits.TRISC2    // Input
    #define USB_BUS_SENSE       1


    /************************************************************************
     *                                                                      *
     *              Application specific definitions                        *
     *                                                                      *
     ************************************************************************/

    #define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER

    // Device Vendor Indentifier (VID)
    #define USB_VID	0x04D8

    // Device Product Indentifier (PID)
    #define USB_PID	0xF25C  // YKAMELEAN24 PID

   
//--------------------------------------------------------
//  CLOCK SETTINGS
//--------------------------------------------------------

#define FCY  2000000        //FCY = CPU Clock / 4 in Hz


#endif
