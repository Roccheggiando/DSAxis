/* 
 * File:   EEPROMdriver.h
 * Author: itrpie
 *
 * Created on 22 settembre 2014, 9.15
 */

#include <stdbool.h>
#include <stdint.h>
#include <p33Fxxxx.h>

#ifndef I2CDRIVER_H
#define	I2CDRIVER_H


//Low Level Functions
uint8_t IdleI2C(void);
uint8_t StartI2C(void);
uint8_t WriteI2C(uint8_t);
uint8_t StopI2C(void);
uint8_t RestartI2C(void);
uint8_t getsI2C(uint8_t*, uint8_t);
uint8_t NotAckI2C(void);
void i2cInit(void);
uint8_t ACKStatus(void);
uint8_t getI2C(void);
uint8_t AckI2C(void);
uint8_t EEAckPolling(uint8_t);



uint8_t HDByteReadI2C(uint8_t, uint8_t, uint8_t, uint8_t*, uint8_t);
uint8_t HDByteWriteI2C(uint8_t, uint8_t, uint8_t, uint8_t);



typedef struct{
    uint8_t ControlByte;
    uint8_t HighAdd;
    uint8_t LowAdd;
    uint8_t rData;
    uint8_t wData;
    uint8_t Length;
    uint8_t PageString[64];

    bool EERead;
    bool EEWrite;
    bool inUse;
    bool dataAvaible;

}EEPROM;

void driverEEPROM(EEPROM* EM);
void runEEPROM(EEPROM* EM);

#endif	/* I2CDRIVER_H */

