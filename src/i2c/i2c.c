/****************************************************************************
 *         Summary: I2C sync communication sample code
 * Processor/Board: PIC24FJ128GB202/PYK24 dev board
 *       Developer: ckuesters@yepkit.com
*****************************************************************************/

#include "i2c.h"
#include <xc.h>
#include <libpic30.h>
#include <string.h> // for strlen

void i2c1_init(unsigned int brg)
{
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
    // enable I2C
    I2C1CONLbits.I2CEN = 1; 
}

void i2c1_shut(void)
{
    // disable I2C
    I2C1CONL = 0;    
}

unsigned char i2c1_reset_bus(void)
{
    unsigned char j;
    // set stop bit
    I2C1CONLbits.PEN = 1;
    // wait until stop bit is cleared
    j = 1; 
    do __delay_us(j > I2C_TIMEUP_COUNTFAST ? I2C_TIMEUP_WAITSLOW : I2C_TIMEUP_WAITFAST) 
            while (I2C1CONLbits.PEN && ++j < I2C_TIMEUP_COUNTMAX);
    return j == I2C_TIMEUP_COUNTMAX;
}

unsigned char i2c1_raw_idle_condition(void)
{
    unsigned char j;
    // wait for idle condition ensuring the master logic is inactive
    j = 1; 
    do __delay_us(j > I2C_TIMEUP_COUNTFAST ? I2C_TIMEUP_WAITSLOW : I2C_TIMEUP_WAITFAST) 
            while ((I2C1CONL & 0x1f) && ++j < I2C_TIMEUP_COUNTMAX);
    return j == I2C_TIMEUP_COUNTMAX;
}

unsigned char i2c1_raw_receive_byte(bool lastbyte, unsigned char *byte)
{
    // wait for idle condition ensuring the master logic is inactive
    if (i2c1_raw_idle_condition() == 0)
    {
        unsigned char j;
        // enable the byte reception
        I2C1CONLbits.RCEN = 1;          
        // wait for receive buffer full
        j = 1; 
        do __delay_us(j > I2C_TIMEUP_COUNTFAST ? I2C_TIMEUP_WAITSLOW : I2C_TIMEUP_WAITFAST) 
                while ((!I2C1STATbits.RBF) && ++j < I2C_TIMEUP_COUNTMAX);
        if (j < I2C_TIMEUP_COUNTMAX)
        {
            // read the byte register
            *byte = I2C1RCV;            
            // wait for idle condition before attempting ACK
            if (i2c1_raw_idle_condition() == 0)
            {
                // ACK bit to send back on receive
                I2C1CONLbits.ACKDT = lastbyte ? 1 : 0;
                // ensure ACK bit transmit is enabled
                I2C1CONLbits.ACKEN = 1;          
                //  wait for completion
                j = 1;
                do __delay_us(j > I2C_TIMEUP_COUNTFAST ? I2C_TIMEUP_WAITSLOW : I2C_TIMEUP_WAITFAST) 
                        while (I2C1CONLbits.ACKEN && ++j < I2C_TIMEUP_COUNTMAX);
                return j == I2C_TIMEUP_COUNTMAX;
            }
        }
    }
    return 1;
}

unsigned char i2c1_raw_send_byte(unsigned char byte)
{
    // wait for idle condition ensuring the master logic is inactive
    if (i2c1_raw_idle_condition() == 0)
    {
        unsigned char j;
        // write the transmit register
        I2C1TRN = byte;
        // then wait until master transmit is complete and acknowledge received
        j = 1; 
        do __delay_us(j > I2C_TIMEUP_COUNTFAST ? I2C_TIMEUP_WAITSLOW : I2C_TIMEUP_WAITFAST) 
                while (I2C1STATbits.TRSTAT && ++j < I2C_TIMEUP_COUNTMAX);
        // return 1 (error) if timeout or NAK
        return j == I2C_TIMEUP_COUNTMAX || I2C1STATbits.ACKSTAT ? 1 : 0;
    }
    return 1;
}

unsigned char i2c1_raw_start_condition(void)
{
    if (i2c1_raw_idle_condition() == 0)
    {
        unsigned char j;
        // initiate a start condition
        I2C1CONLbits.SEN = 1; 
        // then wait for completion
        j = 1; 
        do __delay_us(j > I2C_TIMEUP_COUNTFAST ? I2C_TIMEUP_WAITSLOW : I2C_TIMEUP_WAITFAST) 
                while (I2C1CONLbits.SEN && ++j < I2C_TIMEUP_COUNTMAX);
        return j == I2C_TIMEUP_COUNTMAX;
    }
    return 1;
}

unsigned char i2c1_raw_repeated_start_condition(void)
{
    if (i2c1_raw_idle_condition() == 0)
    {
        unsigned char j;
        // initiate a restart condition on bus
        I2C1CONLbits.RSEN = 1; 
        // then wait for completion
        j = 1; 
        do __delay_us(j > I2C_TIMEUP_COUNTFAST ? I2C_TIMEUP_WAITSLOW : I2C_TIMEUP_WAITFAST) 
                while (I2C1CONLbits.RSEN && ++j < I2C_TIMEUP_COUNTMAX);
        return j == I2C_TIMEUP_COUNTMAX;
    }
    return 1;
}

unsigned char i2c1_raw_stop_condition(void)
{
    // wait for idle condition ensuring the master logic is inactive
    if(i2c1_raw_idle_condition() == 0)
    {
        unsigned char j;
        // then attempt the stop condition any way
        I2C1CONLbits.PEN = 1;
        // wait for completion
        j = 1; 
        do __delay_us(j > I2C_TIMEUP_COUNTFAST ? I2C_TIMEUP_WAITSLOW : I2C_TIMEUP_WAITFAST) 
                while (I2C1CONLbits.PEN && ++j < I2C_TIMEUP_COUNTMAX);
        return j == I2C_TIMEUP_COUNTMAX;
   }
   return 1;
}

bool i2c1_slave_alive(unsigned char slvaddr)
{
    // return true if alive
    unsigned bool result;
    result = i2c1_raw_start_condition() == 0 && i2c1_raw_send_byte(slvaddr << 1 & 0xfe) == 0;
    i2c1_raw_stop_condition();
    return result;
}

unsigned char i2c1_receive_next(bool lastbyte, unsigned char *byte)
{
   // receive the next byte, answer back with:
   //   if lastbyte: send back a not acknowledge telling the slave we are done 
   //                and generate a stop condition on the bus
   //   if not lastbyte: send back an acknowledge telling the slave we are 
   //                    waiting for more data 
   unsigned char result = 1;
   if (i2c1_raw_receive_byte(lastbyte, byte) == 0)
       result = lastbyte ? i2c1_raw_stop_condition() : 0;
   else
       i2c1_raw_stop_condition();
   return result;
}

unsigned char i2c1_receive_first(unsigned char slvaddr, unsigned char regaddr, bool regexist, bool lastbyte, unsigned char *byte)
{
    unsigned char result = 1;
    if (i2c1_raw_start_condition() == 0 && i2c1_raw_send_byte(slvaddr << 1 & 0xfe) == 0)
    {
        // send the register address if exist
        result = regexist ? i2c1_raw_send_byte(regaddr) : 0;
        if (result == 0)
        {
            // submit a restart condition
            result = regexist ? i2c1_raw_repeated_start_condition() : 0;
            // send again the slave address with a read indication
            result |= i2c1_raw_send_byte((slvaddr << 1) | 0x01);
            // receive a byte of data
            result |= i2c1_receive_next(lastbyte, byte);
        }
    }
    else
        i2c1_raw_stop_condition();
    return result;
}

unsigned char i2c1_read_register_byte(unsigned char slvaddr, unsigned char regaddr, unsigned char *byte)
{
    // args: slaveaddr, regaddr, with regaddr = 1, lastbyte = 1, byte buffer pointer
    return i2c1_receive_first(slvaddr, regaddr, true, true, byte);
}

unsigned char i2c1_read_register_word(unsigned char slvaddr, unsigned char regaddr, unsigned int *word)
{
    // first args: slaveaddr, regaddr, with regaddr = 1, lastbyte= 0, high byte buffer pointer
    // next args: lastbyte = 1, low byte buffer pointer
    return i2c1_receive_first(slvaddr, regaddr, true, false, (unsigned char*)(word)) | i2c1_receive_next(true, (unsigned char*)(word+1));
}

unsigned char i2c1_read_byte(unsigned char slvaddr, unsigned char *byte)
{
    // args: slaveaddr, regaddr = null, with regaddr = 0, lastbyte = 1, byte buffer pointer
    return i2c1_receive_first(slvaddr, 0x0, false, true, byte);
}

unsigned char i2c1_read_word(unsigned char slvaddr, unsigned int *word)
{
    // first args: slaveaddr, regaddr = null, with regaddr = 0, lastbyte = 0, high byte buffer pointer
    // next args: lastbyte = 1, low byte buffer pointer
    return i2c1_receive_first(slvaddr, 0x0, false, false, (unsigned char*)(word)) | i2c1_receive_next(true, (unsigned char*)(word+1));
}

unsigned char i2c1_read_data(unsigned char slvaddr, unsigned char *data, unsigned int len)
{
    unsigned char j, ret = 0;
    for (j = 0; j < len && ret == 0; ++j)
        ret |= j > 0 ? i2c1_receive_next(j+1 == len, data+j) : i2c1_receive_first(slvaddr, 0x0, false, j+1 == len, data+j);
    return ret;
}

unsigned char i2c1_send_next(bool lastbyte, unsigned char byte)
{
   return i2c1_raw_send_byte(byte) | (lastbyte ? i2c1_raw_stop_condition() : 0);
}

unsigned char i2c1_send_first(unsigned char slvaddr, unsigned char regaddr, bool regexist, bool lastbyte, unsigned char byte)
{
    unsigned char result = 1;
    // assert a start condition and send the slave address
    if (i2c1_raw_start_condition() == 0 && i2c1_raw_send_byte(slvaddr << 1 & 0xfe) == 0)
    {
        // send the register address if exist
        result = regexist ? i2c1_raw_send_byte(regaddr) : 0;
        // send data to be written
        result |= i2c1_send_next(lastbyte, byte);
    }
    return result;
}

unsigned char i2c1_write_register_byte(unsigned char slvaddr, unsigned char regaddr, unsigned char byte)
{
    // first args: slaveaddr, regaddr, with regaddr = 1, lastbyte = 1, byte value
    return i2c1_send_first(slvaddr, regaddr, true, true, byte);
}

unsigned char i2c1_write_register_word(unsigned char slvaddr, unsigned char regaddr, unsigned int word)
{
    // first args: slaveaddr, regaddr, with regaddr = 1, lastbyte = 0, high byte value
    // next args: lastbyte = 1, low byte value
    return i2c1_send_first(slvaddr, regaddr, true, false, (unsigned char)(*((&word)+0))) 
            | i2c1_send_next(true, (unsigned char)(*((&word)+1)));
}

unsigned char i2c1_write_byte(unsigned char slvaddr, unsigned char byte)
{
    // first args: slaveaddr, regaddr = null, with regaddr = 0, lastbyte = 1, byte value
    return i2c1_send_first(slvaddr, 0x0, false, true, byte);
}

unsigned char i2c1_write_word(unsigned char slvaddr, unsigned int word)
{
    // first args: slaveaddr, regaddr = null, with regaddr = 0, lastbyte = 0, high byte value
    // next args: lastbyte = 1, low byte value
    return i2c1_send_first(slvaddr, 0x0, false, false, (unsigned char)word)
            | i2c1_send_next(true, (unsigned char)(*((&word)+1)));
}

unsigned char i2c1_write_str(unsigned char slvaddr, char *data)
{
    unsigned int len = strlen(data);
    return i2c1_write_data(slvaddr, (unsigned char*)data, len);
}

unsigned char i2c1_write_data(unsigned char slvaddr, unsigned char *data, unsigned int len)
{
    unsigned char j, ret = 0;
    for (j = 0; j < len && ret == 0; ++j)
        ret |= j > 0 ? i2c1_send_next(j+1 == len, data[j]) : i2c1_send_first(slvaddr, 0x0, false, j+1 == len, data[j]);
    return ret;
}

void i2c2_init(unsigned int brg)
{
    // ensure I2C is disabled
    I2C2CONLbits.I2CEN = 0;
    // I2CxBRG = ((1/FSCL - PGDx)*FCY/2)-2
    //   note: PGDx = Delay = Pulse Gobbler Delay
    // example taking FCY = 16000000, FSCL = 400kHz, PGDx = 120ns:
    //   ((1/400000-120/1000000000)*(16000000/2))-2 = 17
    // note: based on FCY = FOSC/2, doze mode and PLL disabled
    // the SCL divider uses 9 bits
    I2C2BRG = (brg > 511 ? 511 : brg);
    // 7-bit slave address
    I2C2CONLbits.A10M = 0; 
    // enable slew rate control for high speed
    I2C2CONLbits.DISSLW = 1;
    // reset stats
    I2C2STAT = 0;
    // enable I2C
    I2C2CONLbits.I2CEN = 1; 
}

void i2c2_shut(void)
{
    // disable I2C
    I2C2CONL = 0;    
}

unsigned char i2c2_reset_bus(void)
{
    unsigned char j;
    // set stop bit
    I2C2CONLbits.PEN = 1;
    // wait until stop bit is cleared
    j = 1; 
    do __delay_us(j > I2C_TIMEUP_COUNTFAST ? I2C_TIMEUP_WAITSLOW : I2C_TIMEUP_WAITFAST) 
            while (I2C2CONLbits.PEN && ++j < I2C_TIMEUP_COUNTMAX);
    return j == I2C_TIMEUP_COUNTMAX;
}

unsigned char i2c2_raw_idle_condition(void)
{
    unsigned char j;
    // wait for idle condition ensuring the master logic is inactive
    j = 1; 
    do __delay_us(j > I2C_TIMEUP_COUNTFAST ? I2C_TIMEUP_WAITSLOW : I2C_TIMEUP_WAITFAST) 
            while ((I2C2CONL & 0x1f) && ++j < I2C_TIMEUP_COUNTMAX);
    return j == I2C_TIMEUP_COUNTMAX;
}

unsigned char i2c2_raw_receive_byte(bool lastbyte, unsigned char *byte)
{
    // wait for idle condition ensuring the master logic is inactive
    if (i2c2_raw_idle_condition() == 0)
    {
        unsigned char j;
        // enable the byte reception
        I2C2CONLbits.RCEN = 1;          
        // wait for receive buffer full
        j = 1; 
        do __delay_us(j > I2C_TIMEUP_COUNTFAST ? I2C_TIMEUP_WAITSLOW : I2C_TIMEUP_WAITFAST) 
                while ((!I2C2STATbits.RBF) && ++j < I2C_TIMEUP_COUNTMAX);
        if (j < I2C_TIMEUP_COUNTMAX)
        {
            // read the byte register
            *byte = I2C2RCV;            
            // wait for idle condition before attempting ACK
            if (i2c2_raw_idle_condition() == 0)
            {
                // ACK bit to send back on receive
                I2C2CONLbits.ACKDT = lastbyte ? 1 : 0;
                // ensure ACK bit transmit is enabled
                I2C2CONLbits.ACKEN = 1;          
                //  wait for completion
                j = 1;
                do __delay_us(j > I2C_TIMEUP_COUNTFAST ? I2C_TIMEUP_WAITSLOW : I2C_TIMEUP_WAITFAST) 
                        while (I2C2CONLbits.ACKEN && ++j < I2C_TIMEUP_COUNTMAX);
                return j == I2C_TIMEUP_COUNTMAX;
            }
        }
    }
    return 1;
}

unsigned char i2c2_raw_send_byte(unsigned char byte)
{
    // wait for idle condition ensuring the master logic is inactive
    if (i2c2_raw_idle_condition() == 0)
    {
        unsigned char j;
        // write the transmit register
        I2C2TRN = byte;
        // then wait until master transmit is complete and acknowledge received
        j = 1; 
        do __delay_us(j > I2C_TIMEUP_COUNTFAST ? I2C_TIMEUP_WAITSLOW : I2C_TIMEUP_WAITFAST) 
                while (I2C2STATbits.TRSTAT && ++j < I2C_TIMEUP_COUNTMAX);
        // return 1 (error) if timeout or NAK
        return j == I2C_TIMEUP_COUNTMAX || I2C2STATbits.ACKSTAT ? 1 : 0;
    }
    return 1;
}

unsigned char i2c2_raw_start_condition(void)
{
    if (i2c2_raw_idle_condition() == 0)
    {
        unsigned char j;
        // initiate a start condition
        I2C2CONLbits.SEN = 1; 
        // then wait for completion
        j = 1; 
        do __delay_us(j > I2C_TIMEUP_COUNTFAST ? I2C_TIMEUP_WAITSLOW : I2C_TIMEUP_WAITFAST) 
                while (I2C2CONLbits.SEN && ++j < I2C_TIMEUP_COUNTMAX);
        return j == I2C_TIMEUP_COUNTMAX;
    }
    return 1;
}

unsigned char i2c2_raw_repeated_start_condition(void)
{
    if (i2c2_raw_idle_condition() == 0)
    {
        unsigned char j;
        // initiate a restart condition on bus
        I2C2CONLbits.RSEN = 1; 
        // then wait for completion
        j = 1; 
        do __delay_us(j > I2C_TIMEUP_COUNTFAST ? I2C_TIMEUP_WAITSLOW : I2C_TIMEUP_WAITFAST) 
                while (I2C2CONLbits.RSEN && ++j < I2C_TIMEUP_COUNTMAX);
        return j == I2C_TIMEUP_COUNTMAX;
    }
    return 1;
}

unsigned char i2c2_raw_stop_condition(void)
{
    // wait for idle condition ensuring the master logic is inactive
    if(i2c2_raw_idle_condition() == 0)
    {
        unsigned char j;
        // then attempt the stop condition any way
        I2C2CONLbits.PEN = 1;
        // wait for completion
        j = 1; 
        do __delay_us(j > I2C_TIMEUP_COUNTFAST ? I2C_TIMEUP_WAITSLOW : I2C_TIMEUP_WAITFAST) 
                while (I2C2CONLbits.PEN && ++j < I2C_TIMEUP_COUNTMAX);
        return j == I2C_TIMEUP_COUNTMAX;
   }
   return 1;
}

bool i2c2_slave_alive(unsigned char slvaddr)
{
    // return true if alive
    unsigned bool result;
    result = i2c2_raw_start_condition() == 0 && i2c2_raw_send_byte(slvaddr << 1 & 0xfe) == 0;
    i2c2_raw_stop_condition();
    return result;
}

unsigned char i2c2_receive_next(bool lastbyte, unsigned char *byte)
{
   // receive the next byte, answer back with:
   //   if lastbyte: send back a not acknowledge telling the slave we are done 
   //                and generate a stop condition on the bus
   //   if not lastbyte: send back an acknowledge telling the slave we are 
   //                    waiting for more data 
   unsigned char result = 1;
   if (i2c2_raw_receive_byte(lastbyte, byte) == 0)
       result = lastbyte ? i2c2_raw_stop_condition() : 0;
   else
       i2c2_raw_stop_condition();
   return result;
}

unsigned char i2c2_receive_first(unsigned char slvaddr, unsigned char regaddr, bool regexist, bool lastbyte, unsigned char *byte)
{
    unsigned char result = 1;
    if (i2c2_raw_start_condition() == 0 && i2c2_raw_send_byte(slvaddr << 1 & 0xfe) == 0)
    {
        // send the register address if exist
        result = regexist ? i2c2_raw_send_byte(regaddr) : 0;
        if (result == 0)
        {
            // submit a restart condition
            result = regexist ? i2c2_raw_repeated_start_condition() : 0;
            // send again the slave address with a read indication
            result |= i2c2_raw_send_byte((slvaddr << 1) | 0x01);
            // receive a byte of data
            result |= i2c2_receive_next(lastbyte, byte);
        }
    }
    else
        i2c2_raw_stop_condition();
    return result;
}

unsigned char i2c2_read_register_byte(unsigned char slvaddr, unsigned char regaddr, unsigned char *byte)
{
    // args: slaveaddr, regaddr, with regaddr = 1, lastbyte = 1, byte buffer pointer
    return i2c2_receive_first(slvaddr, regaddr, true, true, byte);
}

unsigned char i2c2_read_register_word(unsigned char slvaddr, unsigned char regaddr, unsigned int *word)
{
    // first args: slaveaddr, regaddr, with regaddr = 1, lastbyte= 0, high byte buffer pointer
    // next args: lastbyte = 1, low byte buffer pointer
    return i2c2_receive_first(slvaddr, regaddr, true, false, (unsigned char*)(word)) | i2c2_receive_next(true, (unsigned char*)(word+1));
}

unsigned char i2c2_read_byte(unsigned char slvaddr, unsigned char *byte)
{
    // args: slaveaddr, regaddr = null, with regaddr = 0, lastbyte = 1, byte buffer pointer
    return i2c2_receive_first(slvaddr, 0x0, false, true, byte);
}

unsigned char i2c2_read_word(unsigned char slvaddr, unsigned int *word)
{
    // first args: slaveaddr, regaddr = null, with regaddr = 0, lastbyte = 0, high byte buffer pointer
    // next args: lastbyte = 1, low byte buffer pointer
    return i2c2_receive_first(slvaddr, 0x0, false, false, (unsigned char*)(word)) | i2c2_receive_next(true, (unsigned char*)(word+1));
}

unsigned char i2c2_read_data(unsigned char slvaddr, unsigned char *data, unsigned int len)
{
    unsigned char j, ret = 0;
    for (j = 0; j < len && ret == 0; ++j)
        ret |= j > 0 ? i2c2_receive_next(j+1 == len, data+j) : i2c2_receive_first(slvaddr, 0x0, false, j+1 == len, data+j);
    return ret;
}

unsigned char i2c2_send_next(bool lastbyte, unsigned char byte)
{
   return i2c2_raw_send_byte(byte) | (lastbyte ? i2c2_raw_stop_condition() : 0);
}

unsigned char i2c2_send_first(unsigned char slvaddr, unsigned char regaddr, bool regexist, bool lastbyte, unsigned char byte)
{
    unsigned char result = 1;
    // assert a start condition and send the slave address
    if (i2c2_raw_start_condition() == 0 && i2c2_raw_send_byte(slvaddr << 1 & 0xfe) == 0)
    {
        // send the register address if exist
        result = regexist ? i2c2_raw_send_byte(regaddr) : 0;
        // send data to be written
        result |= i2c2_send_next(lastbyte, byte);
    }
    return result;
}

unsigned char i2c2_write_register_byte(unsigned char slvaddr, unsigned char regaddr, unsigned char byte)
{
    // first args: slaveaddr, regaddr, with regaddr = 1, lastbyte = 1, byte value
    return i2c2_send_first(slvaddr, regaddr, true, true, byte);
}

unsigned char i2c2_write_register_word(unsigned char slvaddr, unsigned char regaddr, unsigned int word)
{
    // first args: slaveaddr, regaddr, with regaddr = 1, lastbyte = 0, high byte value
    // next args: lastbyte = 1, low byte value
    return i2c2_send_first(slvaddr, regaddr, true, false, (unsigned char)(*((&word)+0))) 
            | i2c2_send_next(true, (unsigned char)(*((&word)+1)));
}

unsigned char i2c2_write_byte(unsigned char slvaddr, unsigned char byte)
{
    // first args: slaveaddr, regaddr = null, with regaddr = 0, lastbyte = 1, byte value
    return i2c2_send_first(slvaddr, 0x0, false, true, byte);
}

unsigned char i2c2_write_word(unsigned char slvaddr, unsigned int word)
{
    // first args: slaveaddr, regaddr = null, with regaddr = 0, lastbyte = 0, high byte value
    // next args: lastbyte = 1, low byte value
    return i2c2_send_first(slvaddr, 0x0, false, false, (unsigned char)word)
            | i2c2_send_next(true, (unsigned char)(*((&word)+1)));
}

unsigned char i2c2_write_str(unsigned char slvaddr, char *data)
{
    unsigned int len = strlen(data);
    return i2c2_write_data(slvaddr, (unsigned char*)data, len);
}

unsigned char i2c2_write_data(unsigned char slvaddr, unsigned char *data, unsigned int len)
{
    unsigned char j, ret = 0;
    for (j = 0; j < len && ret == 0; ++j)
        ret |= j > 0 ? i2c2_send_next(j+1 == len, data[j]) : i2c2_send_first(slvaddr, 0x0, false, j+1 == len, data[j]);
    return ret;
}
