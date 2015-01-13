#include "CANdriver.h"

ECAN1MSGBUF ecan1msgBuf __attribute__((space(dma), aligned(ECAN1_MSG_BUF_LENGTH * 16)));
mID rx_ecan1message;


/* Dma Initialization for ECAN1 Transmission */
void dma0Init(void) {

    DMACS0 = 0;
    DMA0CON = 0x2020;
    DMA0PAD = 0x0442; /* ECAN 1 (C1TXD) */
    DMA0CNT = 0x0007;
    DMA0REQ = 0x0046; /* ECAN 1 Transmit */
    DMA0STA = __builtin_dmaoffset(ecan1msgBuf);
    DMA0CONbits.CHEN = 1;

}

/* Dma Initialization for ECAN1 Reception */
void dma2Init(void) {

    DMACS0 = 0;
    DMA2CON = 0x0020;
    DMA2PAD = 0x0440; /* ECAN 1 (C1RXD) */
    DMA2CNT = 0x0007;
    DMA2REQ = 0x0022; /* ECAN 1 Receive */
    DMA2STA = __builtin_dmaoffset(ecan1msgBuf);
    DMA2CONbits.CHEN = 1;

}

void ecan1ClkInit(void) {

    C1CTRL1bits.CANCKS = 0x1;

    /*
    Bit Time = (Sync Segment + Propagation Delay + Phase Segment 1 + Phase Segment 2)=20*TQ
    Phase Segment 1 = 8TQ
    Phase Segment 2 = 6Tq
    Propagation Delay = 5Tq
    Sync Segment = 1TQ
    CiCFG1<BRP> =(FCAN /(2 ×N×FBAUD))– 1
     */

    /* Synchronization Jump Width set to 4 TQ */
    C1CFG1bits.SJW = 0x3;
    /* Baud Rate Prescaler */
    C1CFG1bits.BRP = BRP_VAL;


    /* Phase Segment 1 time is 8 TQ */
    C1CFG2bits.SEG1PH = 0x7;
    /* Phase Segment 2 time is set to be programmable */
    C1CFG2bits.SEG2PHTS = 0x1;
    /* Phase Segment 2 time is 6 TQ */
    C1CFG2bits.SEG2PH = 0x5;
    /* Propagation Segment time is 5 TQ */
    C1CFG2bits.PRSEG = 0x4;
    /* Bus line is sampled three times at the sample point */
    C1CFG2bits.SAM = 0x1;



}

void ecan1Init(void) {

    /* Request Configuration Mode */
    C1CTRL1bits.REQOP = 4;
    while (C1CTRL1bits.OPMODE != 4);

    ecan1ClkInit();

    C1FCTRLbits.DMABS = 0b001; /* 4 CAN Message Buffers in DMA RAM */

    /* FILTERS */
    ecan1WriteRxAcptFilter(1,0x21F, 0, 1, 0);
    ecan1WriteRxAcptMask(1, 0xFFF, 1, 1);


    /* Enter Normal Mode */
    C1CTRL1bits.REQOP = 0;
    while (C1CTRL1bits.OPMODE != 0);

    /* ECAN transmit/receive message control */

    C1RXFUL1 = C1RXFUL2 = C1RXOVF1 = C1RXOVF2 = 0x0000;
    C1TR01CONbits.TXEN0 = 1; /* ECAN1, Buffer 0 is a Transmit Buffer */
    C1TR01CONbits.TXEN1 = 0; /* ECAN1, Buffer 1 is a Receive Buffer */
    C1TR01CONbits.TX0PRI = 0b11; /* Message Buffer 0 Priority Level */
    C1TR01CONbits.TX1PRI = 0b11; /* Message Buffer 1 Priority Level */

}

/*
This function configures Acceptance Filter "n"

Inputs:
n-> Filter number [0-15]
identifier-> Bit ordering is given below
Filter Identifier (29-bits) : 0b000f ffff ffff ffff ffff ffff ffff ffff
                                   |____________|_____________________|
                                         SID10:0           EID17:0


Filter Identifier (11-bits) : 0b0000 0000 0000 0000 0000 0fff ffff ffff
                                                          |___________|
                                                             SID10:0
exide -> "0" for standard identifier
 *       "1" for Extended identifier

bufPnt -> Message buffer to store filtered message [0-15]
maskSel -> Optinal Masking of identifier bits [0-3]

 */

void ecan1WriteRxAcptFilter(int n, long identifier, unsigned int exide, unsigned int bufPnt, unsigned int maskSel) {

    unsigned long sid10_0 = 0, eid15_0 = 0, eid17_16 = 0;
    unsigned int *sidRegAddr, *bufPntRegAddr, *maskSelRegAddr, *fltEnRegAddr;


    C1CTRL1bits.WIN = 1;

    // Obtain the Address of CiRXFnSID, CiBUFPNTn, CiFMSKSELn and CiFEN register for a given filter number "n"
    sidRegAddr = (unsigned int *) (&C1RXF0SID + (n << 1));
    bufPntRegAddr = (unsigned int *) (&C1BUFPNT1 + (n >> 2));
    maskSelRegAddr = (unsigned int *) (&C1FMSKSEL1 + (n >> 3));
    fltEnRegAddr = (unsigned int *) (&C1FEN1);


    // Bit-filed manupulation to write to Filter identifier register
    if (exide == 1) { // Filter Extended Identifier
        eid15_0 = (identifier & 0xFFFF);
        eid17_16 = (identifier >> 16) & 0x3;
        sid10_0 = (identifier >> 18) & 0x7FF;

        *sidRegAddr = (((sid10_0) << 5) + 0x8) + eid17_16; // Write to CiRXFnSID Register
        *(sidRegAddr + 1) = eid15_0; // Write to CiRXFnEID Register

    } else { // Filter Standard Identifier
        sid10_0 = (identifier & 0x7FF);
        *sidRegAddr = (sid10_0) << 5; // Write to CiRXFnSID Register
        *(sidRegAddr + 1) = 0; // Write to CiRXFnEID Register
    }


    *bufPntRegAddr = (*bufPntRegAddr) & (0xFFFF - (0xF << (4 * (n & 3)))); // clear nibble
    *bufPntRegAddr = ((bufPnt << (4 * (n & 3))) | (*bufPntRegAddr)); // Write to C1BUFPNTn Register

    *maskSelRegAddr = (*maskSelRegAddr) & (0xFFFF - (0x3 << ((n & 7) * 2))); // clear 2 bits
    *maskSelRegAddr = ((maskSel << (2 * (n & 7))) | (*maskSelRegAddr)); // Write to C1FMSKSELn Register

    *fltEnRegAddr = ((0x1 << n) | (*fltEnRegAddr)); // Write to C1FEN1 Register

    C1CTRL1bits.WIN = 0;


}

/*
This function configures Acceptance Filter Mask "m"

Inputs:
m-> Mask number [0-2]
identifier-> Bit ordering is given below
Filter Mask Identifier (29-bits) : 0b000f ffff ffff ffff ffff ffff ffff ffff
                                        |____________|_____________________|
                                           SID10:0           EID17:0


Filter Mask Identifier (11-bits) : 0b0000 0000 0000 0000 0000 0fff ffff ffff
                                                               |___________|
                                                                  SID10:0

mide ->  "0"  Match either standard or extended address message if filters match
         "1"  Match only message types that correpond to 'exide' bit in filter

 */

void ecan1WriteRxAcptMask(int m, long identifier, unsigned int mide, unsigned int exide) {

    unsigned long sid10_0 = 0, eid15_0 = 0, eid17_16 = 0;
    unsigned int *maskRegAddr;


    C1CTRL1bits.WIN = 1;

    // Obtain the Address of CiRXMmSID register for given Mask number "m"
    maskRegAddr = (unsigned int *) (&C1RXM0SID + (m << 1));

    // Bit-filed manupulation to write to Filter Mask register
    if (exide == 1) { // Filter Extended Identifier
        eid15_0 = (identifier & 0xFFFF);
        eid17_16 = (identifier >> 16) & 0x3;
        sid10_0 = (identifier >> 18) & 0x7FF;

        if (mide == 1)
            *maskRegAddr = ((sid10_0) << 5) + 0x0008 + eid17_16; // Write to CiRXMnSID Register
        else
            *maskRegAddr = ((sid10_0) << 5) + eid17_16; // Write to CiRXMnSID Register
        *(maskRegAddr + 1) = eid15_0; // Write to CiRXMnEID Register

    } else { // Filter Standard Identifier
        sid10_0 = (identifier & 0x7FF);
        if (mide == 1)
            *maskRegAddr = ((sid10_0) << 5) + 0x0008; // Write to CiRXMnSID Register
        else
            *maskRegAddr = (sid10_0) << 5; // Write to CiRXMnSID Register

        *(maskRegAddr + 1) = 0; // Write to CiRXMnEID Register
    }


    C1CTRL1bits.WIN = 0;

}

/* ECAN Transmit Message Buffer Configuration

Inputs:
buf	-> Transmit Buffer Number

txIdentifier ->

Extended Identifier (29-bits) : 0b000f ffff ffff ffff ffff ffff ffff ffff
                                                                     |____________|_____________________|
                                                                                SID10:0           EID17:0



Standard Identifier (11-bits) : 0b0000 0000 0000 0000 0000 0fff ffff ffff
                                                                                                                    |___________|
                                                                                                                              SID10:0

Standard Message Format:
                                                                                        Word0 : 0b000f ffff ffff ffff
                                                                                                             |____________|||___
                                                                                                                SID10:0   SRR   IDE

                                                                                        Word1 : 0b0000 0000 0000 0000
                                                                                                                   |____________|
                                                                                                                          EID17:6

                                                                                        Word2 : 0b0000 00f0 0000 ffff
                                                                                                          |_____||	  	 |__|
                                                                                                          EID5:0 RTR   	  DLC



Extended Message Format:
                                                                                        Word0 : 0b000f ffff ffff ffff
                                                                                                             |____________|||___
                                                                                                                SID10:0   SRR   IDE

                                                                                        Word1 : 0b0000 ffff ffff ffff
                                                                                                                   |____________|
                                                                                                                          EID17:6

                                                                                        Word2 : 0bffff fff0 0000 ffff
                                                                                                          |_____||	  	 |__|
                                                                                                          EID5:0 RTR   	  DLC

ide -> "0"  Message will transmit standard identifier
           "1"  Message will transmit extended identifier



remoteTransmit -> "0" Message transmitted is a normal message
                                  "1" Message transmitted is a remote message

                                Standard Message Format:
                                                                                        Word0 : 0b000f ffff ffff ff1f
                                                                                                             |____________|||___
                                                                                                                SID10:0   SRR   IDE

                                                                                        Word1 : 0b0000 0000 0000 0000
                                                                                                                   |____________|
                                                                                                                          EID17:6

                                                                                        Word2 : 0b0000 0010 0000 ffff
                                                                                                          |_____||	  	 |__|
                                                                                                          EID5:0 RTR   	  DLC



                                Extended Message Format:
                                                                                        Word0 : 0b000f ffff ffff ff1f
                                                                                                             |____________|||___
                                                                                                                SID10:0   SRR   IDE

                                                                                        Word1 : 0b0000 ffff ffff ffff
                                                                                                                   |____________|
                                                                                                                          EID17:6

                                                                                        Word2 : 0bffff ff10 0000 ffff
                                                                                                          |_____||	  	 |__|
                                                                                                          EID5:0 RTR   	  DLC

 */

void ecan1WriteTxMsgBufId(unsigned int buf, long txIdentifier, unsigned int ide, unsigned int remoteTransmit) {

    unsigned long word0 = 0, word1 = 0, word2 = 0;
    unsigned long sid10_0 = 0, eid5_0 = 0, eid17_6 = 0;


    if (ide) {
        eid5_0 = (txIdentifier & 0x3F);
        eid17_6 = (txIdentifier >> 6) & 0xFFF;
        sid10_0 = (txIdentifier >> 18) & 0x7FF;
        word1 = eid17_6;
    } else {
        sid10_0 = (txIdentifier & 0x7FF);
    }


    if (remoteTransmit == 1) { // Transmit Remote Frame

        word0 = ((sid10_0 << 2) | ide | 0x2);
        word2 = ((eid5_0 << 10) | 0x0200);
    } else {

        word0 = ((sid10_0 << 2) | ide);
        word2 = (eid5_0 << 10);
    }

    // Obtain the Address of Transmit Buffer in DMA RAM for a given Transmit Buffer number

    if (ide)
        ecan1msgBuf[buf][0] = (word0 | 0x0002);
    else
        ecan1msgBuf[buf][0] = word0;

    ecan1msgBuf[buf][1] = word1;
    ecan1msgBuf[buf][2] = word2;
}

/* ECAN Transmit Data

Inputs :
buf -> Transmit Buffer Number

dataLength -> Length of Data in Bytes to be transmitted

data1/data2/data3/data4 ->  Transmit Data Bytes

 */

void ecan1WriteTxMsgBufData(unsigned int buf, unsigned int dataLength, unsigned int data1, unsigned int data2, unsigned int data3, unsigned int data4) {

    ecan1msgBuf[buf][2] = ((ecan1msgBuf[buf][2] & 0xFFF0) + dataLength);

    ecan1msgBuf[buf][3] = data1;
    ecan1msgBuf[buf][4] = data2;
    ecan1msgBuf[buf][5] = data3;
    ecan1msgBuf[buf][6] = data4;

}

void ecan1DisableRXFilter(int n) {
    unsigned int *fltEnRegAddr;
    C1CTRL1bits.WIN = 1;
    fltEnRegAddr = (unsigned int *) (&C1FEN1);
    *fltEnRegAddr = (*fltEnRegAddr) & (0xFFFF - (0x1 << n));
    C1CTRL1bits.WIN = 0;

}

void rxECAN1(mID *message) {
    unsigned int ide = 0;
    unsigned int srr = 0;
    unsigned long id = 0;

    ide = ecan1msgBuf[message->buffer][0] & 0x0001;
    srr = ecan1msgBuf[message->buffer][0] & 0x0002;

    /* check to see what type of message it is */
    /* message is standard identifier */
    if (ide == 0) {
        message->id = (ecan1msgBuf[message->buffer][0] & 0x1FFC) >> 2;
        message->frame_type = CAN_FRAME_STD;
    }/* mesage is extended identifier */
    else {
        id = ecan1msgBuf[message->buffer][0] & 0x1FFC;
        message->id = id << 16;
        id = ecan1msgBuf[message->buffer][1] & 0x0FFF;
        message->id = message->id + (id << 6);
        id = (ecan1msgBuf[message->buffer][2] & 0xFC00) >> 10;
        message->id = message->id + id;
        message->frame_type = CAN_FRAME_EXT;
    }
    /* check to see what type of message it is */
    /* RTR message */
    if (srr == 1) {
        message->message_type = CAN_MSG_RTR;
    }/* normal message */
    else {
        message->message_type = CAN_MSG_DATA;
        message->data[0] = (unsigned char) ecan1msgBuf[message->buffer][3];
        message->data[1] = (unsigned char) ((ecan1msgBuf[message->buffer][3] & 0xFF00) >> 8);
        message->data[2] = (unsigned char) ecan1msgBuf[message->buffer][4];
        message->data[3] = (unsigned char) ((ecan1msgBuf[message->buffer][4] & 0xFF00) >> 8);
        message->data[4] = (unsigned char) ecan1msgBuf[message->buffer][5];
        message->data[5] = (unsigned char) ((ecan1msgBuf[message->buffer][5] & 0xFF00) >> 8);
        message->data[6] = (unsigned char) ecan1msgBuf[message->buffer][6];
        message->data[7] = (unsigned char) ((ecan1msgBuf[message->buffer][6] & 0xFF00) >> 8);
        message->data_length = (unsigned char) (ecan1msgBuf[message->buffer][2] & 0x000F);
    }
}

void ecan1WriteMessage() {

    ecan1WriteTxMsgBufId(0, 0x13F, 0, 0);
    ecan1WriteTxMsgBufData(0, 8, 'a', 'b', 0x3333, 0x4444);

}

void __attribute__((interrupt, no_auto_psv))_C1Interrupt(void) {
    IFS2bits.C1IF = 0; // clear interrupt flag
    if (C1INTFbits.TBIF) {
        C1INTFbits.TBIF = 0;
    }

    if (C1INTFbits.RBIF) {
        // read the message
        if (C1RXFUL1bits.RXFUL1 == 1) {
            rx_ecan1message.buffer = 1;
            C1RXFUL1bits.RXFUL1 = 0;
        }
        rxECAN1(&rx_ecan1message);
        C1INTFbits.RBIF = 0;
    }
}

void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void) {
    IFS0bits.DMA0IF = 0; // Clear the DMA0 Interrupt Flag;
}

void __attribute__((interrupt, no_auto_psv)) _DMA2Interrupt(void) {
    IFS1bits.DMA2IF = 0; // Clear the DMA2 Interrupt Flag;
}

void sendCanMessage(long identifier, unsigned int dataLength, unsigned int* data) {

    ecan1WriteTxMsgBufId(0, identifier, 0, 0);
    ecan1WriteTxMsgBufDataStr(0, dataLength, data);
    C1TR01CONbits.TXREQ0 = 1;
}

void ecan1WriteTxMsgBufDataStr(unsigned int buf, unsigned int dataLength, unsigned int* data) {

    ecan1msgBuf[buf][2] = ((ecan1msgBuf[buf][2] & 0xFFF0) + dataLength);
    int i;
    for (i = 0; i < dataLength; i++)
        ecan1msgBuf[buf][3 + i] = *(data + i);

}
