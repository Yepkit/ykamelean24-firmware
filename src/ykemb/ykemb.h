/*
    ykemb.h
*/


#ifndef _YKEMB_H
#define _YKEMB_H


unsigned char ykemb_i2cInit(unsigned int brg);

unsigned char ykemb_byteWrite(unsigned char dataByte, unsigned char deviceAddr, unsigned char* wrtAddr);

unsigned char ykemb_i2cSelByteRead(unsigned char deviceAddr, unsigned char* readPrevAddr, unsigned char* byteBuff);


#endif



