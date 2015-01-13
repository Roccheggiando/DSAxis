#include "app/FIF.h"
#include "app/EEPROM.h"
#include "app/AXIS.h"
#include "app/CAN.h"

#ifndef SYSTEM_H
#define	SYSTEM_H

typedef struct {
    PRAGMA_FIF_OBJ FIF_OBJ;
    PRAGMA_EEPROM_OBJ EEPROM_OBJ;
    PRAGMA_AXIS_OBJ AXIS_OBJ;
    PRAGMA_CAN_OBJ CAN_OBJ;

}SYSTEM_OBJECTS;

void systemInit();
void scheduler();

#endif	/* SYSTEM_H */

