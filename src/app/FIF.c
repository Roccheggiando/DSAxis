#include "FIF.h"

PRAGMA_FIF_OBJ PRAGMA_FIF_Initialize(PRAGMA_FIF_CONFIG config) {
    PRAGMA_FIF_OBJ F;
    F.FIF.SELF = config.FIF_MAP;
    F.FIF.RTR = 1;
    F.FIF.RTS = 0;
    F.FIF.DESTINATION = 0x00;
    F.FIF.TIP = 0;

    F.PRAGMA_FIF_cntMAP = config.PRAGMA_FIF_cntMAP;
    F.state = READY;
    return F;
}

void PRAGMA_FIF_ADD_TO_MAP(PRAGMA_FIF_OBJ F, PRAGMA_FIF_INTERFACE* module) {
    F.PRAGMA_FIF_MAP[F.PRAGMA_FIF_cntMAP] = module;
    F.PRAGMA_FIF_cntMAP++;
}

PRAGMA_FIF_INTERFACE* PRAGMA_FIF_Find_RTR(PRAGMA_FIF_OBJ F, PRAGMA_FIF_INTERFACE* sender) {
    int i;
    for (i = 0; i < F.PRAGMA_FIF_cntMAP; i++) {
        if (F.PRAGMA_FIF_MAP[i]->SELF == sender->DESTINATION) {
            return F.PRAGMA_FIF_MAP[i];
        }
    }
    return sender;
}

void PRAGMA_FIF_Task(PRAGMA_FIF_OBJ F) {
    F.state = RUN;
    PRAGMA_FIF_INTERFACE* rts;
    PRAGMA_FIF_INTERFACE* rtr;
    int i;
    for (i = 0; i < F.PRAGMA_FIF_cntMAP; i++) {
        rts = F.PRAGMA_FIF_MAP[i];
        //Check every module for ready to sent flag
        if (rts->RTS == 1) {
            rtr = PRAGMA_FIF_Find_RTR(F, rts);
            //check if the destination module is able to receive the data
            if (rtr != rts && rtr->RTR == 1 && rtr->TIP) {

                /* Clear destination.rtr transfer data and clear source.rts*/
                rtr->RTR = 0;
                rtr->SOURCE = rts->SELF;
                rtr->MODULE_REGISTER = rts->MODULE_REGISTER;
                rts->RTS = 0;

                /* If trasfer is done and the sender module is in trasfer in progress.
                 The TIP flag is cleared*/
                if (rts->TIP == 1)
                    rts->TIP = 0;
            }
        }
    }
}


