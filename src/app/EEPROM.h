#include "PRAGMA.h"
#include "../board/CerebotMC/I2Cdriver.h"
#ifndef EEPROM_H
#define	EEPROM_H

typedef enum {
    READ,
    WRITE
} PRAGMA_EEPROM_DIRECTION;

typedef struct {
    PRAGMA_MODULE_STATE state;

    PRAGMA_EEPROM_DIRECTION DIR;
    int PRAGMA_EEPROM_cntMAP;
    PRAGMA_EEPROM_INTERFACE* PRAGMA_EEPROM_MAP[20];

    uint8_t ControlByte;
    uint8_t HIGH;
    uint8_t LOW;
    uint8_t* rData;
    uint8_t* wData;
} PRAGMA_EEPROM_OBJ;

typedef struct {
    int PRAGMA_EEPROM_cntMAP;

    uint8_t FIF_MAP;
    uint8_t ControlByte;
} PRAGMA_EEPROM_CONFIG;


void PRAGMA_EEPROM_ADD_TO_MAP(PRAGMA_EEPROM_OBJ F, PRAGMA_EEPROM_INTERFACE* module);
PRAGMA_EEPROM_OBJ PRAGMA_EEPROM_Initialize(PRAGMA_EEPROM_CONFIG);
void PRAGMA_EEPROM_Task(PRAGMA_EEPROM_OBJ);

#endif	/* EEPROM_H */

