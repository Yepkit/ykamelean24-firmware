/*! \file 
 * YKUR Module for YKAMELEAN24 firmware.
 */

#ifndef _YKUR_H_
#define _YKUR_H_


/*!
 * Sends the command to the addressed YKUR board. 
 *
 * 
 *
 * \param     cmd_buffer          char pointer to the buffer containing 
 *                          the command to be sent to YKUR.
 *
 * \param     num_bytes           bytes from the cmd_buffer to be sent
 *                          to YKUR.
 *
 * \param     address             YKUR board I2C address. The 7 less significant
 *                          bits contain the address.
 *
 *  Output:
 *
 *     * 0  -> OK
 *     * 1 ->  Error
 *
 */
char ykur_i2cSendCommand(unsigned char cmd_buffer, char num_bytes, unsigned char address);

/*!
 * Reads the response from the YKUR board. 
 *
 * 
 *
 * \param     cmd_buffer          char pointer to the buffer containing 
 *                          the resonse read from YKUR.
 *
 *
 * \param     address             YKUR board I2C address. The 7 less significant
 *                          bits contain the address.
 *
 *  Output:
 *
 *     * 0  ->                  OK
 *
 *     * 1 ->                  Error
 *
 *
 */
char ykur_i2cGetResponse(char *cmd_buffer, char address);






    

#endif

