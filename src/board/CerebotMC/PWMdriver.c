#ifndef __PWMDRIVER__
#define __PWMDRIVER__

#include <pwm.h>
#include "PWMdriver.h"

void pwmInit(void) {

    /* PWM  [11]                                                                                                         */
    /*---------------------------------------------------------------------------*/
    // Holds the value to be loaded into dutycycle register
    unsigned int period;
    // Holds the value to be loaded into special event compare register
    unsigned int sptime;
    // Holds PWM configuration value
    unsigned int config1;
    // Holds the value be loaded into PWMCON1 register
    unsigned int config2;
    // Holds the value to config the special event trigger postscale and dutycycle
    unsigned int config3;

    // Config PWM
    period = 2048;
    // PWM F=19,340Hz counting UP 12bit resolution @ Fcy=39.628 MHz (osc 7.3728MHz)
    // PWM F=19,522Hz counting UP 12bit resolution @ Fcy=39.628 MHz (osc 10MHz)
    sptime = 0x0;
    // 1:1 postscaler, 1:1 prescale, free running mode
    // PWM time base ON, count up
    config1 = PWM_EN & PWM_IDLE_CON & PWM_OP_SCALE1 & PWM_IPCLK_SCALE1 &
            PWM_MOD_FREE;
    // PWM1H e PWM1L enabled in complementar mode
    // dsPICs with 3 pairs of PWM pins have one timer only (A)
    config2 = PWM_MOD1_COMP & PWM_PEN1L & PWM_PEN1H & PWM_MOD2_COMP & PWM_PEN2L & PWM_PEN2H & PWM_PDIS3H & PWM_PDIS3L;

    config3 = PWM_SEVOPS1 & PWM_OSYNC_PWM & PWM_UEN;
    //OpenMCPWM1(period, sptime, config1, config2, config3);
    OpenMCPWM(period, sptime, config1, config2, config3);
    // Dead Time Unit A assigned to both 1 & 2 PWM pairs
    /* SetMCPWM1DeadTimeAssignment(PWM1_DTS1A_UA & PWM1_DTS1I_UA &                                                      PWM1_DTS2A_UA & PWM1_DTS2I_UA);
     */
    P1DTCON2bits.DTS1A = 0;
    P1DTCON2bits.DTS1I = 0;
    P1DTCON2bits.DTS2A = 0;
    P1DTCON2bits.DTS2I = 0;

    // Dead time 100ns = 0.2% of PWM period
    SetMCPWMDeadTimeGeneration(PWM_DTA4 & PWM_DTAPS1);

    // dutycyclereg=1, dutycycle=50% (motore fermo in LAP mode , updatedisable=0
    SetDCMCPWM(1, 2048, 0);
    SetDCMCPWM(2, 2048, 0);


}

#endif
