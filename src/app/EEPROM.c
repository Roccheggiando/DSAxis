#include "EEPROM.h"

PRAGMA_EEPROM_OBJ PRAGMA_EEPROM_Initialize(PRAGMA_EEPROM_CONFIG config) {
    PRAGMA_EEPROM_OBJ E;
    E.PRAGMA_EEPROM_cntMAP = config.PRAGMA_EEPROM_cntMAP;
    E.ControlByte = config.ControlByte;
    E.state = READY;
    return E;
}

void PRAGMA_EEPROM_Task(PRAGMA_EEPROM_OBJ E) {
    uint8_t i;
    for (i = 0; i < E.PRAGMA_EEPROM_cntMAP; i++)
        if (E.PRAGMA_EEPROM_MAP[i]->RTS == 1) {  //search pending requests
            if (E.PRAGMA_EEPROM_MAP[i]->rw == 0) //type of request
                E.DIR = READ;
            else
                E.DIR = WRITE;
            E.HIGH = E.PRAGMA_EEPROM_MAP[i]->high;
            E.LOW = E.PRAGMA_EEPROM_MAP[i]->low;
            E.rData = E.PRAGMA_EEPROM_MAP[i]->rData;
            E.wData = E.PRAGMA_EEPROM_MAP[i]->wData;

            if (E.DIR == READ){
                HDByteReadI2C(E.ControlByte, E.HIGH, E.LOW, E.rData, 1);
                E.PRAGMA_EEPROM_MAP[i]->REPLIED = 1;
            }
            if (E.DIR == WRITE)
                HDByteWriteI2C(E.ControlByte, E.HIGH, E.LOW, *E.wData);

            E.PRAGMA_EEPROM_MAP[i]->RTS = 0;
        }

}

void PRAGMA_EEPROM_ADD_TO_MAP(PRAGMA_EEPROM_OBJ E, PRAGMA_EEPROM_INTERFACE* module) {
    E.PRAGMA_EEPROM_MAP[E.PRAGMA_EEPROM_cntMAP] = module;
    E.PRAGMA_EEPROM_cntMAP++;
}