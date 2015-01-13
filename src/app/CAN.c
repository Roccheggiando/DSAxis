#include "CAN.h"

PRAGMA_CAN_OBJ PRAGMA_CAN_Initialize(PRAGMA_CAN_CONFIG config) {
    PRAGMA_CAN_OBJ C;
    C.PRAGMA_CAN_cntMAP = config.PRAGMA_CAN_cntMAP;

    /* Request Configuration Mode */
    C1CTRL1bits.REQOP = 4;
    while (C1CTRL1bits.OPMODE != 4);

    ecan1ClkInit();

    C1FCTRLbits.DMABS = 0b001; /* 4 CAN Message Buffers in DMA RAM */

    ecan1WriteRxAcptMask(0, 0xFFFF, 1, 1);


    int i;
    for (i = 0; i < C.PRAGMA_CAN_cntMAP; i++) {
        long id = (C.filter_base_identifier << 1) + C.PRAGMA_CAN_MAP[i]->SELF;
        ecan1WriteRxAcptFilter(i, id, 0, 1, 0);
    }

    /* Enter Normal Mode */
    C1CTRL1bits.REQOP = 0;
    while (C1CTRL1bits.OPMODE != 0);

    /* ECAN transmit/receive message control */

    C1RXFUL1 = C1RXFUL2 = C1RXOVF1 = C1RXOVF2 = 0x0000;
    C1TR01CONbits.TXEN0 = 1; /* ECAN1, Buffer 0 is a Transmit Buffer */
    C1TR01CONbits.TXEN1 = 0; /* ECAN1, Buffer 1 is a Receive Buffer */
    C1TR01CONbits.TX0PRI = 0b11; /* Message Buffer 0 Priority Level */
    C1TR01CONbits.TX1PRI = 0b11; /* Message Buffer 1 Priority Level */

    return C;
}

void PRAGMA_CAN_ADD_TO_MAP(PRAGMA_CAN_OBJ C, PRAGMA_CAN_INTERFACE* module) {
    C.PRAGMA_CAN_MAP[C.PRAGMA_CAN_cntMAP] = module;
    C.PRAGMA_CAN_cntMAP++;
}

/* Controlla se il buffer di ricezione é pieno e smista i messaggi al modulo destinatario */

void PRAGMA_CAN_Task(PRAGMA_CAN_OBJ C) {

    //Received Message
    if (rx_ecan1message.buffer == 1) {
        PRAGMA_CAN_INTERFACE* I;
        uint8_t mapped_module = rx_ecan1message.id & 0x3; //CAN_INTEFACE->SELF
        I = PRAGMA_CAN_FIND_MODULE(C, mapped_module);
        I->RETRIVED = 1;
        I->dataLen = rx_ecan1message.data_length;
        int i;
        for  (i=0; i < I->dataLen; i++)
            I->BUFFER_IN[i] = rx_ecan1message.data[i];

        rx_ecan1message.buffer = 0;
    }

    //Send Message routine.
    int i;
    for (i = 0; i < C.PRAGMA_CAN_cntMAP; i++)
        if (C.PRAGMA_CAN_MAP[i]->RTS == 1){
            C.PRAGMA_CAN_MAP[i]->RTS = 0;
            long id = (C.filter_base_identifier << 1) + (C.PRAGMA_CAN_MAP[i]->SELF + 1);
            sendCanMessage(id, C.PRAGMA_CAN_MAP[i]->dataLen, C.PRAGMA_CAN_MAP[i]->BUFFER_OUT);
        }

}

PRAGMA_CAN_INTERFACE* PRAGMA_CAN_FIND_MODULE(PRAGMA_CAN_OBJ C, uint8_t MAP) {
    int i;
    PRAGMA_CAN_INTERFACE* I;
    for (i = 0; i < C.PRAGMA_CAN_cntMAP; i++)
        if (C.PRAGMA_CAN_MAP[i]->SELF == MAP)
            I = C.PRAGMA_CAN_MAP[i];

    return I;
}
