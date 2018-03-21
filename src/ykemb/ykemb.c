/*
    ykemb.c

TODO: Substituir este header pela licença
*/


#include <xc.h>
#include "ykemb.h"
#include "../i2c/i2c.h"


unsigned char ykemb_i2c_idle() {
    do
        Nop();
    while (I2C1CONL & 0x1f);

    return 0;
}




/*************************************************************************
                        ykemb_i2cInit
--------------------------------------------------------------------------
Description:
    
    Initializes the I2C module for communication with YKEMB.

Inputs:


Outputs:


Dependencies:


*************************************************************************/
unsigned char ykemb_i2cInit(unsigned int brg) {

    unsigned char status = 0;


#ifndef USE_I2C_LIB

    // ensure I2C is disabled
    I2C1CONLbits.I2CEN = 0;
    // I2CxBRG = ((1/FSCL - PGDx)*FCY/2)-2
    //   note: PGDx = Delay = Pulse Gobbler Delay
    // example taking FCY = 16000000, FSCL = 400kHz, PGDx = 120ns:
    //   ((1/400000-120/1000000000)*(16000000/2))-2 = 17
    // note: based on FCY = FOSC/2, doze mode and PLL disabled
    // the SCL divider uses 9 bits
    I2C1BRG = (brg > 511 ? 511 : brg);
    
    // 7-bit slave address
    I2C1CONLbits.A10M = 0; 
    // enable slew rate control for high speed
    I2C1CONLbits.DISSLW = 1;
    
    // reset stats
    I2C1STAT = 0;
    // Enable I2C module
    I2C1CONLbits.I2CEN = 1;
    
#else

    i2c1_init();

#endif


    return status;
}




/*************************************************************************
                        ykemb_byteWrite
--------------------------------------------------------------------------
Description:
    
    Implements a Byte Write to the YKEMB EEPROM using I2C module 1.

    In Byte Write mode the Master sends a START, followed by Slave address,
    two byte address and data to be written. The Slave acknowledges all 4 
    bytes, and the Master then follows up with a STOP, which in turn starts 
    the internal Write operation. During internal Write, the Slave will not
    acknowledge any Read or Write request from the Master.

Inputs:
    
    char deviceAddr             -   Byte containing the three board address
                                    bits (the select switch bits).
                                    Must be 0x00000aaa format where "a" 
                                    denotes the address bit.

Outputs:


Dependencies:

    ykemb_i2cInit()             -   I2C module need to be initiated
                                    before attempting a call on a
                                    byte write.


*************************************************************************/
unsigned char ykemb_byteWrite(unsigned char dataByte, unsigned char deviceAddr, unsigned char* wrtAddr) {
  
    unsigned char error = 0;

    // 1. Initiate START event
    // -----------------------
    ykemb_i2c_idle();
    I2C1CONLbits.SEN = 1;
    // then wait for completion
    // ToDo: Insert max time condition 
    do 
        Nop();
    while (I2C1CONLbits.SEN);
     

    // 2. Send the I2C device address byte w/ write bit
    // ------------------------------------------------
    
    ykemb_i2c_idle();
    
    I2C1TRNbits.I2CTXDATA = ((deviceAddr | 0b01010000) << 1) & 0b11111110;    
    // Wait for and verify an Acknowledge from the slave
    // Wait for transmission
    while (I2C1STATbits.TRSTAT == 1) {};
    // Check ACK
    if (I2C1STATbits.ACKSTAT == 1) {
        // Write error
        error = 1;
        return error;     
    }
    
    // 3. Send the memory two bytes write address
    // ------------------------------------------

    ykemb_i2c_idle();
    // Send first byte (A15 to A8)
    I2C1TRNbits.I2CTXDATA = wrtAddr[0];
    // Wait for and verify an Acknowledge from the slave
    // Wait for transmission
    while (I2C1STATbits.TRSTAT == 1) {};
    // Check ACK
    if (I2C1STATbits.ACKSTAT == 1) {
        // Write error
        error = 2;
        return error;     
    }
    // Send the second byte (A7 to A0)
    ykemb_i2c_idle();
    I2C1TRNbits.I2CTXDATA = wrtAddr[1];
    // Wait for and verify an Acknowledge from the slave
    // Wait for transmission
    while (I2C1STATbits.TRSTAT == 1) {};
    // Check ACK
    if (I2C1STATbits.ACKSTAT == 1) {
        // Write error
        error = 3;
        return error;     
    }
 
    // 4. Send the data byte
    // ---------------------

    ykemb_i2c_idle();

    I2C1TRNbits.I2CTXDATA = dataByte;
    // Wait for and verify an Acknowledge from the slave
    // Wait for transmission
    while (I2C1STATbits.TRSTAT == 1) {};
    // Check ACK
    if (I2C1STATbits.ACKSTAT == 1) {
        // Write error
        error = 4;
        return error;     
    }
 
    // 5. Generate STOP condition
    // --------------------------
    
    // Clear master logic
   /* 
    I2C1CONLbits.ACKEN = 0;
    I2C1CONLbits.RCEN = 0;
    I2C1CONLbits.PEN = 0;
    I2C1CONLbits.RSEN = 0;
    I2C1CONLbits.SEN = 0;
     */

    ykemb_i2c_idle();
    // Initiate stop
    I2C1CONLbits.PEN = 1;
    do 
        Nop();
    while (I2C1CONLbits.PEN);


    return error;
}





unsigned char ykemb_i2cSelByteRead(unsigned char deviceAddr, unsigned char* readPrevAddr, unsigned char* byteBuff) {
   
    unsigned char error = 0;

    // 1. DUMMY WRITE: START event
    // ---------------------------
#ifndef USE_I2C_LIB
    do
        Nop();
    while (I2C1CONL & 0x1f);

    I2C1CONLbits.SEN = 1;
    // then wait for completion
    // ToDo: Insert max time condition 
    do 
        Nop();
    while (I2C1CONLbits.SEN);
 
#else
    i2c2_raw_repeated_start_condition();   
#endif

    // 2. DUMMY WRITE: Slave address w/ write bit
    // ---------------------------------------------
    I2C1TRNbits.I2CTXDATA = ((deviceAddr | 0b01010000) << 1) & 0b11111110;    
    // Wait for and verify an Acknowledge from the slave
    // Wait for transmission
    while (I2C1STATbits.TRSTAT == 1) {};
    // Check ACK
    if (I2C1STATbits.ACKSTAT == 1) {
        // Write error
        error = 1;
        return error;     
    }
    
    
    // 3. DUMMY WRITE: Send the memory two bytes previous byte read address
    // --------------------------------------------------------------------
    // Send first byte (A15 to A8)
    I2C1TRNbits.I2CTXDATA = readPrevAddr[0];
    // Wait for and verify an Acknowledge from the slave
    // Wait for transmission
    while (I2C1STATbits.TRSTAT == 1) {};
    // Check ACK
    if (I2C1STATbits.ACKSTAT == 1) {
        // Write error
        error = 2;
        return error;     
    }
    // Send the second byte (A7 to A0)
    I2C1TRNbits.I2CTXDATA = readPrevAddr[1];
    // Wait for and verify an Acknowledge from the slave
    // Wait for transmission
    while (I2C1STATbits.TRSTAT == 1) {};
    // Check ACK
    if (I2C1STATbits.ACKSTAT == 1) {
        // Write error
        error = 3;
        return error;     
    }

    // ---------------------------------------------------
    // Immediate Address Read
    // ---------------------------------------------------

    // 5. New START (RESTART) event
    // ------------------
    I2C1CONLbits.RSEN = 1;
    //I2C1CONLbits.SEN = 1;
    // ToDo: Insert max time condition 
    do 
        Nop();
    while (I2C1CONLbits.RSEN);
 

    // 6. Slave address w/ read bit
    // ----------------------------
    I2C1TRNbits.I2CTXDATA = ((deviceAddr | 0b01010000) << 1) | 0b00000001;    
    // Wait for and verify an Acknowledge from the slave
    // Wait for transmission
    while (I2C1STATbits.TRSTAT == 1) {};
    // Check ACK
    if (I2C1STATbits.ACKSTAT == 1) {
        // Write error
        error = 4;
        return error;     
    }
    
    // 7. Enable Master Reception
    // --------------------------
    I2C1CONLbits.RCEN = 1;

    // 8. Read received byte
    // ---------------------
    // Wait
    while (I2C1STATbits.RBF == 0){};
    // Read to buffer
    *byteBuff = I2C1RCVbits.I2CRXDATA;

    // 9. NACK
    // -------

    ykemb_i2c_idle();
    I2C1CONLbits.ACKDT = 1;
    I2C1CONLbits.ACKEN = 1;
    do 
        Nop();
    while (I2C1CONLbits.ACKEN);

    // 10. STOP
    // --------
    // Initiate stop
    I2C1CONLbits.PEN = 1;
    do 
        Nop();
    while (I2C1CONLbits.PEN);

    // Clear master logic
    
    I2C1CONLbits.ACKEN = 0;
    I2C1CONLbits.RCEN = 0;
    I2C1CONLbits.PEN = 0;
    I2C1CONLbits.RSEN = 0;
    I2C1CONLbits.SEN = 0;
      

    return error;

}


