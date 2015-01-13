#include <p33Fxxxx.h>
#include <pwm.h>
#include <stdint.h>
#include <dsp.h>
#include "PRAGMA.h"

#ifdef EEPROM_STORE
#include "EEPROM.h"
#endif

#ifndef AXIS_H
#define	AXIS_H

//#define MOT_24V

typedef enum {
    AXIS_RUN,
    AXIS_STOP,
    AXIS_INIT,
    AXIS_STILL
} PRAGMA_AXIS_STATE;

typedef enum {
    DC,
    STEPPER,
    BRUSHLESS
} PRAGMA_AXIS_MOT_TYPE;

typedef enum {
    AXIS_NOPE,
    AXIS_START,
    AXIS_SOFTSTOP,
    AXIS_REINIT,
    AXIS_SAVE
} PRAGMA_AXIS_CMD;

typedef struct {
#ifdef EEPROM_STORE
    PRAGMA_EEPROM_INTERFACE EI;
    uint8_t eData;
#endif
    PRAGMA_CAN_INTERFACE CAN;
    
    PRAGMA_FIF_INTERFACE FIF;
    PRAGMA_MODULE_STATE state;

    PRAGMA_AXIS_MOT_TYPE mot;
    PRAGMA_AXIS_STATE axisState;
    PRAGMA_AXIS_CMD cmd;

    unsigned int QEI[2]; //[k,k-1]
    unsigned int REF;
    unsigned int DISTANCE;
    unsigned int VEL;
    unsigned int DC[2];
    unsigned int PID;
    int ERROR[2];
    float K[3]; //EEPROM subaddress: 0x 0,1,2 /1000
    int maxPIDOUT;
    int WINDUP;
    int PR, IN, DR;
} PRAGMA_AXIS_OBJ;

typedef struct {
    uint8_t MAP;
    PRAGMA_AXIS_MOT_TYPE mot;
    PRAGMA_AXIS_STATE axisState;
    PRAGMA_AXIS_CMD cmd;

    int ERROR[2];
    float K[3];
    int maxPIDOUT;
    int WINDUP;
    int PR, IN, DR;
    
} PRAGMA_AXIS_CONFIG;

PRAGMA_AXIS_OBJ PRAGMA_AXIS_Initialize(PRAGMA_AXIS_CONFIG);
void PRAGMA_AXIS_Task(PRAGMA_AXIS_OBJ);

void PRAGMA_AXIS_PID(PRAGMA_AXIS_OBJ A);
#endif	/* AXIS_H */

