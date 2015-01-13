/* 
 * File:   main.c
 * Author: itrpie
 *
 * Created on 21 settembre 2014, 16.44
 */
#include <p33Fxxxx.h>
#include <stdio.h>
#include <stdlib.h>

#include "board/CerebotMC/board.h"
#include "app/FIF.h"
#include "system_facilities.h"

_FOSC(FCKSM_CSECMD & POSCMD_XT)
_FOSCSEL(FNOSC_FRC)
_FWDT(FWDTEN_OFF)
_FPOR(FPWRT_PWR1)
_FICD(JTAGEN_OFF & ICS_PGD1)

extern SYSTEM_OBJECTS SO;

int main(int argc, char** argv) {
    
    boardInit();
    systemInit();
    
    while(1) {
        scheduler();
    }

    return (EXIT_SUCCESS);
}

