# YKAMELEAN24 Firmware Project


Native firmware for the YKAMELEAN24 microcontroller development boards.


Description
===========


Microcontrollers (MCU) are an integrating piece of many electronic systems providing the ability to implement complex control systems and interface with a wide range of peripherals.
They provide a high flexibility, cost efficiency and footprint savings.

Nonetheless starting the development of a MCU based system from "green field" may be a daunting task due to the learning curve associated with programming it.
This is the main reason why the "accelerated" development MCU boards and tools proliferate nowadays, boards like arduino and the tools associated with it brought the power of MCU environments to the general public and leveraged the development of new an exiting DIY projects and systems.


We use extensively MCU development boards on our development process, testing development hypothesis and for implementing "one-shot" projects/systems.
With time the features we looked for become more apparent and the high level design for our "ideal" development MCU board was born.

The main features we wanted in a MCU development board were:
- Out of the box functionality that allowed us to plug and play with it.
- Quick and easy programming capability.
- Uncompromising in terms of evolution to production level.

YKAMELEAN24 was developed to provide the above features to developers.
It provides a solid functional baseline to build upon and enrich.

The native firmware provides a fully functional baseline that can be used in a plug and play manner together with a PC with an USB connecting to provide out-of-the-box capability for the user to interact with the low level electronic interfaces using the MCU IOs and interfaces/peripherals.
A software for Linux and Windows is available for download at the YKAMELEAN24 product page which implements the commands used to control the board, peripherals and add-on modules.
Add-on modules implement the interface with additional boards like sensors and actuators.

The native firmware is structured to facilitate the inclusion of additional code from the user and is suitable to serve a baseline to be built upon.
It will take care of initialization the basic configuration of the YKAMELEAN24 board (for example the USB interface configuration) saving time to the developer. 


A USB bootloader is used to enable direct loading of the firmware to the board through USB, this way a specific hardware programmer is not required facilitating the development process.
To load the firmware through USB we provide a PC software application available for download at the [product page](https://www.yepkit.com/product/300105/YKAMELEAN24).


While having a way to quickly implement "something" is useful we also wanted to do it with a production level orientation where code efficiency, minimize rework, ability to use all of the MCU features, to incorporate native Manufacturer libraries and tools is important.
By using the native C programming language, libraries and compilers we ensure uncompromising development from inception to production.



Add-on boards/modules supported
===============================
- YKUR
- YKHaT
- TS100


Licensing
=========

The source code is licensed Apache License, Version 2.0. 
Refer to [LICENSE](LICENSE.md) file.





For more information and resources please visit the [yepkit website YKAMELEAN24 page](https://www.yepkit.com/product/300105/YKAMELEAN24).









