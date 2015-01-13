#include "TIMERdriver.h"

void oscInit(void) {

    PLLFBD = (int) (40 - 2);
    CLKDIVbits.PLLPOST = 0; // N1=2
    CLKDIVbits.PLLPRE = 0; // N2=2
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(0x01);
    while (OSCCONbits.COSC != 0b011);
    // Wait for PLL to lock
    while (OSCCONbits.LOCK != 1);
}


void timerInit(void) {
    /* TIMER 2 AS 16BIT TIMER */
    T2CON = 0;
    TMR2 = 0;

    T2CONbits.T32 = 0;

    T2CONbits.TCS = 0;

    PR2 = TIMER_2_MATCH;

    IPC1bits.T2IP = 0x01;
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1;

    T2CONbits.TCKPS0 = 1;
    T2CONbits.TCKPS1 = 0;

    T2CONbits.TON = 1;
}

