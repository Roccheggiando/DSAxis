#include "QEIdriver.h"

void qeiInit(void) {
    //    ADPCFG |= 0x0038; // Configure QEI pins as digital inputs
    /*QEI1CONbits.QEIM = 0; // Disable QEI Module
    QEI1CONbits.CNTERR = 0; // Clear any count errors
    QEI1CONbits.QEISIDL = 0; // Continue operation during sleep
    QEI1CONbits.SWPAB = 0; // QEA and QEB not swapped
    QEI1CONbits.PCDOUT = 0; // Normal I/O pin operation
    QEI1CONbits.POSRES = 0; // Index pulse resets position counter
    DFLT1CONbits.CEID = 1; // Count error interrupts disabled
    DFLT1CONbits.QEOUT = 1; // Digital filters output enabled for QEn pins
    DFLT1CONbits.QECK = 5; // 1:64 clock divide for digital filter for QEn
    POS1CNT = 0; // Reset position counter
    QEI1CONbits.QEIM = 7; // X1 mode with position counter reset by Index
    MAX1CNT = 0xFFFF;*/
    AD1PCFGL |= 0xFFFF;
    AD2PCFGL |= 0xFFFF;

    QEI1CONbits.QEISIDL = 0; // Continue module operation in idle mode
    QEI1CONbits.UPDN = 1; // Position Counter Direction is positive (+)
    QEI1CONbits.INDX = 1; // Read only - Index pin state status pin.
    QEI1CONbits.QEIM0 = 0; // Use 4x Update mode with reset on index reset
    QEI1CONbits.QEIM1 = 1; // "
    QEI1CONbits.QEIM2 = 1; // "
    QEI1CONbits.SWPAB = 0; // Phase A and Phase B inputs are not swapped
    QEI1CONbits.PCDOUT = 0; // Counter Direction Status Output (Normal I/O pin operation)
    QEI1CONbits.POSRES = 0; // Index Pulse resets Position Counter
    DFLT1CONbits.CEID = 1; // Interrupts due to count errors are disabled
    DFLT1CONbits.QEOUT = 1; // Digital filter outputs enabled
    DFLT1CONbits.QECK0 = 0; // 1:128 clock divide for digital filter for Index
    DFLT1CONbits.QECK1 = 1; // "
    DFLT1CONbits.QECK2 = 1; // "
    MAX1CNT = 0xFFFF;
    POS1CNT = 0;
}


