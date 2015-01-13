#include "I2Cdriver.h"

void i2cInit(void) {
    //This function will initialize the I2C(1) peripheral.
    //First set the I2C(1) BRG Baud Rate.

    //Consult the dSPIC Data Sheet for information on how to calculate the
    //Baud Rate.
    // I2CBRG = [( 1/Fscl - PGD)*Fcy]-2
    // Fscl = 100kHz
    // Fcy = 40mHz
    // PGD = 130ns

    I2C2BRG = 0x018E;

    //Now we will initialise the I2C peripheral for Master Mode, No Slew Rate
    //Control, and leave the peripheral switched off.

    I2C2CON = 0x1200;

    I2C2RCV = 0x0000;
    I2C2TRN = 0x0000;
    //Now we can enable the peripheral

    I2C2CON = 0x9200;
}

uint8_t StartI2C(void) {
    //This function generates an I2C start condition and returns status
    //of the Start.

    I2C2CONbits.SEN = 1; //Generate Start COndition
    while (I2C2CONbits.SEN); //Wait for Start COndition
    return (I2C2STATbits.S); //Optionally return status
}

uint8_t RestartI2C(void) {
    //This function generates an I2C Restart condition and returns status
    //of the Restart.

    I2C2CONbits.RSEN = 1; //Generate Restart
    while (I2C2CONbits.RSEN); //Wait for restart
    return (I2C2STATbits.S); //Optional - return status
}

uint8_t StopI2C(void) {
    //This function generates an I2C stop condition and returns status
    //of the Stop.

    I2C2CONbits.PEN = 1; //Generate Stop Condition
    while (I2C2CONbits.PEN); //Wait for Stop
    return (I2C2STATbits.P); //Optional - return status
}

uint8_t WriteI2C(uint8_t byte) {
    //This function transmits the byte passed to the function
    //while (I2C2STATbits.TRSTAT);	//Wait for bus to be idle
    I2C2TRN = byte; //Load byte to I2C2 Transmit buffer
    while (I2C2STATbits.TBF); //wait for data transmission
    return (0);
}

uint8_t IdleI2C(void) {
    while (I2C2STATbits.TRSTAT); //Wait for bus Idle
    return (0);
}

uint8_t HDByteWriteI2C(uint8_t ControlByte, uint8_t HighAdd, uint8_t LowAdd, uint8_t data) {
    uint8_t ErrorCode;

    IdleI2C(); //Ensure Module is Idle
    StartI2C(); //Generate Start COndition
    WriteI2C(ControlByte); //Write Control byte
    IdleI2C();

    ErrorCode = ACKStatus(); //Return ACK Status

    WriteI2C(HighAdd);
    IdleI2C(); //Write High Address
    WriteI2C(LowAdd); //Write Low Address
    IdleI2C();

    ErrorCode = ACKStatus(); //Return ACK Status

    WriteI2C(data); //Write Data
    IdleI2C();
    StopI2C(); //Initiate Stop Condition
    EEAckPolling(ControlByte); //perform Ack Polling

    return (ErrorCode);
}

uint8_t HDByteReadI2C(uint8_t ControlByte, uint8_t HighAdd, uint8_t LowAdd, uint8_t *Data, uint8_t Length) {
    IdleI2C(); //Wait for bus Idle
    StartI2C(); //Generate Start condition
    WriteI2C(ControlByte); //send control byte for write
    IdleI2C(); //Wait for bus Idle

    WriteI2C(HighAdd); //Send High Address
    IdleI2C(); //Wait for bus Idle
    WriteI2C(LowAdd); //Send Low Address
    IdleI2C(); //Wait for bus Idle

    RestartI2C(); //Generate Restart
    WriteI2C(ControlByte | 0x01); //send control byte for Read
    IdleI2C(); //Wait for bus Idle

    getsI2C(Data, Length); //Read Length number of bytes to Data
    NotAckI2C(); //send Not Ack
    StopI2C(); //Send Stop Condition
    return (0);
}

uint8_t ACKStatus(void) {
    return (!I2C2STATbits.ACKSTAT); //Return Ack Status
}

uint8_t NotAckI2C(void) {
    I2C2CONbits.ACKDT = 1; //Set for NotACk
    I2C2CONbits.ACKEN = 1;
    while (I2C2CONbits.ACKEN); //wait for ACK to complete
    I2C2CONbits.ACKDT = 0; //Set for NotACk
    return (0);
}

uint8_t AckI2C(void) {
    I2C2CONbits.ACKDT = 0; //Set for ACk
    I2C2CONbits.ACKEN = 1;
    while (I2C2CONbits.ACKEN); //wait for ACK to complete
    return (0);
}

uint8_t getsI2C(uint8_t *rdptr, uint8_t Length) {
    while (Length--) {
        *rdptr++ = getI2C(); //get a single byte

        if (I2C2STATbits.BCL) //Test for Bus collision
        {
            return (-1);
        }

        if (Length) {
            AckI2C(); //Acknowledge until all read
        }
    }
    return (0);
}

uint8_t getI2C(void) {
    I2C2CONbits.RCEN = 1; //Enable Master receive
    Nop();
    while (!I2C2STATbits.RBF); //Wait for receive bufer to be full
    return (I2C2RCV); //Return data in buffer
}

uint8_t EEAckPolling(uint8_t control) {
    IdleI2C(); //wait for bus Idle
    StartI2C(); //Generate Start condition

    if (I2C2STATbits.BCL) {
        return (-1); //Bus collision, return
    } else {
        if (WriteI2C(control)) {
            return (-3); //error return
        }

        IdleI2C(); //wait for bus idle
        if (I2C2STATbits.BCL) {
            return (-1); //error return
        }

        while (ACKStatus()) {
            RestartI2C(); //generate restart
            if (I2C2STATbits.BCL) {
                return (-1); //error return
            }

            if (WriteI2C(control)) {
                return (-3);
            }

            IdleI2C();
        }
    }
    StopI2C(); //send stop condition
    if (I2C2STATbits.BCL) {
        return (-1);
    }
    return (0);
}



