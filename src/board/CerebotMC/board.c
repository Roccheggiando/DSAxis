#include "board.h"


void boardInit(){
    oscInit();
    timerInit();
    portsInit();
    pwmInit();
    qeiInit();
    i2cInit();
}