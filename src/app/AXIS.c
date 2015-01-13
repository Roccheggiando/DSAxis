#include "AXIS.h"

int cp;
#define MAX_IMP_REV     360
#define MAX_COUNT_REV   (MAX_IMP_REV * 4) - 1
#define RESOLUTION      360/MAX_COUNT_REV
#define FRAC_RATIO  32768/MAX_COUNT_REV

void PRAGMA_AXIS_Task(PRAGMA_AXIS_OBJ A) {
    //TODO FIF HANDLER
    //TODO CAN HANDLER
    /*---------------------------STOP-----------------------------------------*/
    if (A.axisState == AXIS_STOP)
        SetDCMCPWM(1, 2048, 0);

    /*----------------------INITIALIZATION------------------------------------*/
    if (A.axisState == AXIS_INIT) {
#ifdef EEPROM_STORE
        if (A.EI.REPLIED == 1) {                                //DATI RITORNO
            A.K[A.EI.low] = A.eData / 1000;                     //IMMAGAZINO I DATI
            A.EI.REPLIED = 0;                                   //PRONTO A RICEVERE
        }
        
        if (A.EI.RTS == 0 && A.EI.REPLIED == 0) {               //SE NN ASPETTO NULLA
            A.EI.rw = 0;                                        //LETTURA
            A.EI.rData = &A.eData;                              //AGGIUSTO IL POINTER
            A.EI.high = A.EI.SELF;                              //SETTO L'ADDRESS
            //k[0,1,2]
            A.EI.low = 0x00;                                    //SETTO LEGGO I PRIMI TRE BIT
            if (A.EI.low <= 0x02)
                A.EI.low++;

            A.EI.RTS = 1;
        }
        if(A.EI.low == 2)
            A.axisState = AXIS_RUN;

#else
        A.axisState = AXIS_RUN;
#endif
    }


    /*-----------------------------RUN----------------------------------------*/
    if (A.axisState == AXIS_RUN) {


        if (A.mot == DC) { //Brushed
            A.QEI[0] = POS1CNT;
            A.DISTANCE = A.QEI[0] > A.REF ? A.QEI[0] - A.REF : A.REF - A.QEI[0];
            A.VEL = A.QEI[0] > A.QEI[1] ? A.QEI[0] - A.QEI[1] : A.QEI[1] - A.QEI[0];
            A.QEI[1] = A.QEI[0];

            PRAGMA_AXIS_PID(A);
#ifdef MOT_24V
            A.DC[0] = (A.PID) / 2 + 2048;
#else
            A.DC[0] = A.PID + 2048;
#endif
            SetDCMCPWM(1, A.DC[0], 0);
        }
    }

    //command handler A.cmd


}

PRAGMA_AXIS_OBJ PRAGMA_AXIS_Initialize(PRAGMA_AXIS_CONFIG config) {
    PRAGMA_AXIS_OBJ A;
    A.maxPIDOUT = config.maxPIDOUT;
    A.WINDUP = config.WINDUP;
    A.K[0] = config.K[0];
    A.K[1] = config.K[1];
    A.K[2] = config.K[2];
    A.ERROR[0] = config.ERROR[0];
    A.ERROR[1] = config.ERROR[1];
    A.PR = config.PR;
    A.DR = config.DR;
    A.IN = config.IN;
    
    A.REF = 0;
    A.QEI[0] = 0;
    A.QEI[1] = 0;

    A.EI.RTS = 0;
    A.EI.REPLIED = 0;
    A.EI.SELF = config.MAP;
    
    A.FIF.SELF = config.MAP;
    A.FIF.RTR = 1;
    A.FIF.RTS = 0;
    A.FIF.DESTINATION = 0x00;
    A.FIF.TIP = 0;

    A.CAN.RETRIVED = 0;
    A.CAN.RTS = 0;
    A.CAN.SELF = config.MAP;
    A.CAN.dataLen = 0;
    return A;

}

void PRAGMA_AXIS_PID(PRAGMA_AXIS_OBJ A) {

    A.ERROR[0] = A.REF - A.QEI[0];
    A.PR = A.K[0] * A.ERROR[0];

    A.IN += A.ERROR[0] * A.K[1];
    if (A.IN > A.WINDUP)
        A.IN = A.WINDUP;
    if (A.IN < -A.WINDUP)
        A.IN = -A.WINDUP;

    A.DR = A.K[2] * (A.ERROR[0] - A.ERROR[1]);
    A.ERROR[1] = A.ERROR[0];
    A.PID = (int) A.DR + A.IN + A.PR;

    if (A.PID > A.maxPIDOUT)
        A.PID = A.maxPIDOUT;
    if (A.PID < -A.maxPIDOUT)
        A.PID = -A.maxPIDOUT;

}