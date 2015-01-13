#include <stdbool.h>
#include <stdint.h>

#define EEPROM_STORE

#ifndef PRAGMA_H
#define	PRAGMA_H

typedef enum {
    INIT,
    READY,
    STOP,
    ERROR,
    RUN
} PRAGMA_MODULE_STATE;


//SOCKETS INTERFACES
typedef struct {
    bool RTS;
    bool REPLIED;
    bool rw; //0:read 1:write
    uint8_t high;
    uint8_t low;
    uint8_t* rData;
    uint8_t* wData;
    uint8_t SELF;
} PRAGMA_EEPROM_INTERFACE;

typedef struct {
    bool RTS;
    bool RTR;
    bool TIP;
    uint8_t MODULE_REGISTER;
    uint8_t SELF;
    uint8_t DESTINATION;
    uint8_t SOURCE;

} PRAGMA_FIF_INTERFACE;

typedef struct {
    unsigned int BUFFER_IN[8];
    unsigned int BUFFER_OUT[8];
    unsigned int dataLen;
    uint8_t SELF;
    bool RTS;
    bool RETRIVED;

} PRAGMA_CAN_INTERFACE;


#endif	/* PRAGMA_H */

