#include "system_facilities.h"

SYSTEM_OBJECTS SO;

const PRAGMA_FIF_CONFIG initFIF = {
    .FIF_MAP = 0x00,
    .PRAGMA_FIF_cntMAP = 0
};

const PRAGMA_EEPROM_CONFIG initEEPROM = {
    .ControlByte = 0xA0, //CONTROL BYTE = DEVICE CODE 0xAh| BLOCK ADDRESS (000) | R/W BIT (0) = 0xA0
    .PRAGMA_EEPROM_cntMAP = 0
};

const PRAGMA_CAN_CONFIG initCAN = {
    .PRAGMA_CAN_cntMAP  = 0,
    .filter_base_identifier = 0x12
            
};

const PRAGMA_AXIS_CONFIG initAXIS = {
    .DR = 0,
    .IN = 0,
    .PR = 0,
    .maxPIDOUT = 2048,
    .WINDUP = 500,
    .K[0] = 10,
    .K[1] = 0.1,
    .K[2] = 0.002,
    .ERROR[0] = 0,
    .ERROR[1] = 0,
    .mot = DC,
    .MAP = 0x02,
    .axisState = AXIS_INIT,
    .cmd = AXIS_NOPE
};

void systemInit() {
    SO.FIF_OBJ = PRAGMA_FIF_Initialize(initFIF);
    SO.EEPROM_OBJ = PRAGMA_EEPROM_Initialize(initEEPROM);
    SO.AXIS_OBJ = PRAGMA_AXIS_Initialize(initAXIS);
    SO.CAN_OBJ = PRAGMA_CAN_Initialize(initCAN);

    //POPULATE SOCKETSS
    PRAGMA_FIF_ADD_TO_MAP(SO.FIF_OBJ, &SO.AXIS_OBJ.FIF);
    PRAGMA_EEPROM_ADD_TO_MAP(SO.EEPROM_OBJ, &SO.AXIS_OBJ.EI);
    PRAGMA_CAN_ADD_TO_MAP(SO.CAN_OBJ, &SO.AXIS_OBJ.CAN);            //RX at (0x12 << 1 + 0x2 ) = 0x26
                                                                    //Tx at (0x12 << 1 + 0x2 + 1) = 0x27
    
}

void scheduler() {
    PRAGMA_FIF_Task(SO.FIF_OBJ);
    PRAGMA_EEPROM_Task(SO.EEPROM_OBJ);
    PRAGMA_CAN_Task(SO.CAN_OBJ);
    
    PRAGMA_AXIS_Task(SO.AXIS_OBJ);
}
