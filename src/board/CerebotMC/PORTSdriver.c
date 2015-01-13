#include "PORTSdriver.h"

void portsInit(void) {
    TRISF = 0x0000;
    TRISG = 0x0000;

    // Configre SCA/SDA pin as open-drain
    TRISFbits.TRISF4 = 1;
    TRISFbits.TRISF5 = 1;
    ODCFbits.ODCF4 = 0;
    ODCFbits.ODCF5 = 0;

    /*QEI INPUT*/
    _TRISB3 = 1;
    _TRISB4 = 1;
    _TRISB5 = 1;
    _TRISB6 = 1;
    /*I5 and I6 Button*/
    _TRISB8 = 1;
    _TRISB14 = 1;

    /* DIGITAL INPUT */
    _TRISD0 = 1;
    _TRISD1 = 1;
    _TRISD2 = 1;
    _TRISD3 = 1;
    /* DIGITAL OUTPUT */
    _TRISD4 = 0;
    _TRISD5 = 0;
    _TRISD6 = 0;
    _TRISD7 = 0;
}

