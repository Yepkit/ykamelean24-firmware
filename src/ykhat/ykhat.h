#ifndef _YKHAT_H_
#define _YKHAT_H_



/*************************************************************************
 *
 *                      DEFINES
 *
 *************************************************************************/





/*************************************************************************
 *
 *                      PROTOTYPES
 *
 *************************************************************************/

/*************************************************************************
 * Function: ykhat_get_tempC
 *
 * Inputs:
 *  
 *  addr        sensor device I2C address
 *
 * Outputs:
 *
 *  The function returns the temperature reading in ºC
 *
 ************************************************************************/
int ykhat_get_tempC(char addr);


/*************************************************************************
 * Function: ykhat_get_temp
 *
 * Inputs:
 *  
 *  addr        sensor device I2C address
 *
 * Outputs:
 *
 *  The function returns the temperature reading in ºF
 *
 ************************************************************************/
int ykhat_get_tempF(char addr);


/*************************************************************************
 * Function: ykhat_get_hum
 *
 * Inputs:
 *  
 *  addr        sensor device I2C address
 *
 * Outputs:
 *
 *  The function returns the humidity reading in %RH
 *
 ************************************************************************/
int ykhat_get_hum(char addr);




//-----------------------------------------------------------------------
//
// PRIVATE FUNCTIONS
//
//-----------------------------------------------------------------------

/*************************************************************************
 *  Function: ykhat_i2c_init
 *
 *  Description:
 *
 *      Ensures that all is properly configured and initialized
 *      for the I2C communication with YKHaT boards
 *
 *  Input:
 *
 *      brg                 Baudrate for I2C. 
 *
 *  Output:
 *
 *      0                   OK
 *
 *      1                   Error
 *
 *
 ************************************************************************/          
unsigned char ykur_i2c_init(unsigned int brg);



void ykhat_i2c_idle(void);

void ykhat_start_sensor_reading(char addr);

char ykhat_get_sensor_reading(char addr, char *buffer);

#endif
