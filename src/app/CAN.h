#include "PRAGMA.h"
#include "../board/CerebotMC/CANdriver.h"

#ifndef CAN_H
#define	CAN_H

extern mID rx_ecan1message;

typedef struct {
    int PRAGMA_CAN_cntMAP;
    PRAGMA_CAN_INTERFACE* PRAGMA_CAN_MAP[20];
    
    /* l'indirizzo dei filtri é derivato da
     * address = filter_base_identifier + MAP
     */
    long filter_base_identifier;
   
    
} PRAGMA_CAN_OBJ;

typedef struct {
    int PRAGMA_CAN_cntMAP;
    long filter_base_identifier;
} PRAGMA_CAN_CONFIG;


void PRAGMA_CAN_ADD_TO_MAP(PRAGMA_CAN_OBJ F, PRAGMA_CAN_INTERFACE* module);
PRAGMA_CAN_OBJ PRAGMA_CAN_Initialize(PRAGMA_CAN_CONFIG);
void PRAGMA_CAN_Task(PRAGMA_CAN_OBJ);

PRAGMA_CAN_INTERFACE* PRAGMA_CAN_FIND_MODULE(PRAGMA_CAN_OBJ C, uint8_t MAP);

#endif	/* CAN_H */

    /* Create a filter for every module mapped by the Socket CAN
     * Every module receive on Socket_base_address << 1 + Module_MAP
     * Every module trasmit on Socket_base_address << 1 + Module_MAP + 1
     *
     * Changing the MAP change the address ex.
     * If you want address 0x1a6 and 0x1A7 the formula is and the base address is 0x12
     * MAP = 1A7 - 12 << 1 = 183
     * MAP = ADDRESS -  (BASE << 1)
     *
     * The task should be called every cycle. The task put the data received in the
     * module destination interface and raise the retrived flag. A module can send
     * data via BUFFER_OUT and setting RTS flag and dataLen.
     */