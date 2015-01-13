/*
 * Here is defined the FIF module. It take care about the inter-module communications
 * The paradigma is simple:
 * Every module must have FIF_INTERFACE, and it must be configured with a FIF address.
 * Every time a module want to comunicate with another module, it must:
 * - prepare data in to FIF.MODULEREGISER
 * - set the fif destination address to FIF.DESTINATION
 * - set the FIF.RTS bit.
 *
 * If the destination is available the trasfer is delivered before the next
 * execution of the sender module.
 *
 * Also in the FIF object is defined a FIF interface with address 0x00, this will used
 * in future for syncronize complex data transfer, as data stream or communication bridge.
 *
 * FIF module must be called as first module, by the scheduler, every cycle.
 */

#include "PRAGMA.h"

#ifndef FIF_H
#define	FIF_H

typedef struct {
    PRAGMA_FIF_INTERFACE FIF;
    int PRAGMA_FIF_cntMAP;
    PRAGMA_MODULE_STATE state;

    PRAGMA_FIF_INTERFACE* PRAGMA_FIF_MAP[20];
} PRAGMA_FIF_OBJ;

typedef struct{
    uint8_t FIF_MAP;
    int PRAGMA_FIF_cntMAP;
}PRAGMA_FIF_CONFIG;


PRAGMA_FIF_OBJ PRAGMA_FIF_Initialize(PRAGMA_FIF_CONFIG);
void PRAGMA_FIF_Task(PRAGMA_FIF_OBJ);


//internal funcions
void PRAGMA_FIF_ADD_TO_MAP(PRAGMA_FIF_OBJ F, PRAGMA_FIF_INTERFACE* module);
PRAGMA_FIF_INTERFACE* PRAGMA_FIF_Find_RTR(PRAGMA_FIF_OBJ F, PRAGMA_FIF_INTERFACE* sender);

#endif	/* FIF_H */

