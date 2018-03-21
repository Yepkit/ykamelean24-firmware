/*! \file
 * 
 */

#include <xc.h>
#include "inc/system.h"



//#include <pin_manager.h>


//TODO: Criar a função ykamelean24Init para substituir initYPPIC24...


/********************************************************************
 * Function:        int initYKPIC24(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          Returns ZERO at success.
 *
 * Side Effects:    System configured.
 *
 * Overview:        Configures the system.
 *
 *                  User application initialization routine should
 *                  also be called from here.
 *
 * Note:            None
 *******************************************************************/
int initYkamelean24(void) {     //TODO: Substituir esta função pela "initBoard()"

    //TODO: COMENTAR O CODIGO!!!
    // CPDIV 1:1; PLLEN enabled; RCDIV FRC/1; DOZE 1:8; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3020;
    // STOR disabled; STORPOL Interrupt when STOR is 1; STSIDL disabled; STLPOL Interrupt when STLOCK is 1; STLOCK disabled; STSRC SOSC; STEN disabled; TUN Center frequency; 
    OSCTUN = 0x0000;
    // ROEN disabled; ROSEL FOSC; ROSIDL disabled; ROSWEN disabled; ROOUT disabled; ROSLP disabled; 
    REFOCONL = 0x0000;
    // RODIV 0; 
    REFOCONH = 0x0000;
    // ROTRIM 0; 
    REFOTRIML = 0x0000;
    
    
    //PIN_MANAGER_Initialize();
    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPD1 = 0x0000;
    CNPD2 = 0x0000;
    CNPD3 = 0x0000;
    CNPU1 = 0x0000;
    CNPU2 = 0x0000;
    CNPU3 = 0x0000;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;
    
    /** SETUP FOR USB OPERATION ****************************************/
    
    //OSCCONbits.SOSCEN = 0b0;
   /* OSCCONbits.SOSCEN = 0;
    OSCCONbits.POSCEN = 0;
    OSCCONbits.CLKLOCK = 0;
    OSCCONbits.OSWEN = 0;
    OSCCONbits.IOLOCK = 0;
    */
    
    /*
    //CLKDIV REGISTER
    CLKDIVbits.RCDIV = 0b001;
    CLKDIVbits.CPDIV = 0b01;
    CLKDIVbits.PLLEN = 0b0;

    //OSCTUN REGISTER
    OSCTUNbits.STEN = 0b1;
    OSCTUNbits.STSRC = 0b0;
    OSCTUNbits.STSIDL = 0b0;
*/
    
    //Set anaolg I/O's to Digital
    ANSB = 0;       //Set PORTB I/O's to Digital
    ANSA = 0;       //Set PORTB I/O's to Digital       
    
    
    //Turn Red LED ON
    TRISBbits.TRISB0 = 0;   
    //LATBbits.LATB0 = 1;  
    PORTBbits.RB0 = 1;
    
    
/** CONFIGURE I/O's FOR SPI WITH MCP3551 ********************************/
    // RB2 -> SDI
    // RB3 -> SCKOUT
    // RB7 -> CS
    
    //SDI
    //TRISBbits.TRISB2 = 1;   //Set to Input
    
    //SCKOUT
    //TRISBbits.TRISB3 = 0;   //Set to Output
    //LATBbits.LATB3 = 1;     //Init to High (transfer occurs on Hight to Low transitions)
        
    //CS
    //TRISBbits.TRISB7 = 0;   //Set to Output
    //LATBbits.LATB7 = 1;     //Init to chip selected
    
    
    
// SPI Configuration
    
// SPI Peripheral Pin Select
    // Pin Mapping:
    //      RB1 -> SDO
    //      RB4 -> SDI
    //      RB7 -> SCK
    //
    // Process:
    //      1. Unlock PPS Registers
    //      2. Configure inputs
    //      3. Configure outputs
    //      4. Lock PPS Register
    
/*    
// 1. Unlock PPS Registers
    asm volatile    ("MOV   #OSCCON, W1     \n"
                     "MOV   #0x46, W2       \n"
                     "MOV   #0x57, W3       \n"
                     "MOV.b W2, [W1]        \n"
                     "MOV.b W3, [W1]        \n"
                     "BCLR  OSCCON, #6");
    
// 2. Configure inputs: SDI/RB4
    // Assign SDI1 to RB4(RPI4)
    RPINR20bits.SDI1R = 4;
    
// 3. Configure outputs: SDO/RB1 and SCK/RB7
    // Assign SCK1OUT to RB7(RP7)
    RPOR3bits.RP7R = 8;
    // Assign SDO to RB1(RP1)
    RPOR0bits.RP1R = 7;
    // Assign SSO1 (Slave Chip Select) to RA0(RP5)
    //RPOR2bits.RP5R = 9;
    
    
// 4. Lock PPS Registers
    asm volatile    ("MOV   #OSCCON, W1     \n"
                     "MOV   #0x46, W2       \n"
                     "MOV   #0x57, W3       \n"
                     "MOV.b W2, [W1]        \n"
                     "MOV.b W3, [W1]        \n"
                     "BSET  OSCCON, #6");
    
// Initialize SPI1 in Master Mode
    // Disable SPI1 interrupts
    IEC3bits.SPI1RXIE = 0;
    // Stop and Reset SPI module
    SPI1CON1Lbits.SPIEN = 0;
    // Set standard buffer mode
    SPI1CON1Lbits.ENHBUF = 0;
    // Define baud rate
    SPI1BRGL = 1;
    // Clear SPI1 Receive Overflow bit
    SPI1STATLbits.SPIROV = 0;
    // Set Master Mode
    SPI1CON1Lbits.MSTEN = 1;
    // Set the Word Length to 25 bits
    SPI1CON2Lbits.WLENGTH = 0b11000;
    // Configure clock to Idle in High Level
    SPI1CON1Lbits.CKP = 1;
    // Transmission in falling edge of the clock
    SPI1CON1Lbits.CKE = 0;
    // Slave chip select by I/O pin
    SPI1CON1Hbits.MSSEN = 0;
    // Disable SDO (Just receives)
    SPI1CON1Lbits.DISSDO = 1;
    // Data sample at the midle of clock period (rising edge in this case)
    SPI1CON1Lbits.SMP = 0;
    // Enable SPI operation
    SPI1CON1Lbits.SPIEN = 1;
    
    
  */
    
    
    /** Initialize the other I/O's ******************************************/
    

    //RB1
    TRISBbits.TRISB1 = 0;   //Set to Output
    LATBbits.LATB1 = 0;     //test...

    //RB2
    TRISBbits.TRISB2 = 0;   //Set to Output
    LATBbits.LATB2 = 0;     //test...
    
    //RB3
    TRISBbits.TRISB3 = 0;   //Set to Output
    LATBbits.LATB3 = 0;     //test...
    
    //RB7
    TRISBbits.TRISB7 = 0;   //Set to Output
    LATBbits.LATB7 = 0;     //test...
    
    //RB8
    TRISBbits.TRISB8 = 0;   //Set to Output
    LATBbits.LATB8 = 0;     //test...
    
    //RB9
    TRISBbits.TRISB9 = 0;   //Set to Output
    LATBbits.LATB9 = 0;     //test...
 
    //RB13
    TRISBbits.TRISB13 = 0;   //Set to Output
    LATBbits.LATB13 = 0;     //test...OK
   
    //RB14
    TRISBbits.TRISB14 = 0;   //Set to Output
    LATBbits.LATB14 = 0;     //test...OK
      
    //RB15
    TRISBbits.TRISB15 = 0;   //Set to Output
    LATBbits.LATB15 = 0;     //test...OK
    
    //RA0 
    TRISAbits.TRISA0 = 0;   //Set to Output
    PORTAbits.RA0 = 0;
    
    //RA1
    TRISAbits.TRISA1 = 0;   //Set to Output
    LATAbits.LATA1 = 0;     //test...OK
    
    //RA2
    TRISAbits.TRISA2 = 0;   //Set to Output
    LATAbits.LATA2 = 0;     //test...OK
    
    //RA3
    TRISAbits.TRISA3 = 0;   //Set to Output
    LATAbits.LATA3 = 0;     //test...OK
    
  
    

    
    
    
    
    return 0;
}
    
    
    

    
    

