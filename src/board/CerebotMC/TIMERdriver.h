#include <p33Fxxxx.h>

#ifndef TIMERDRIVER_H
#define	TIMERDRIVER_H

#define CPU_CLK_RATE 32000000L
#define PERIPH_CLOCK_RATE (CPU_CLK_RATE/2L)

#define TIMER_2_RATE 1000L
#define TIMER_2_PRE  64L        // clock rate is (32000000/2)/64 = 250 KHz
#define TIMER_2_MATCH (PERIPH_CLOCK_RATE/(TIMER_2_RATE * TIMER_2_PRE))

void timerInit();
void oscInit();

#endif	/* PWMDRIVER_H */

