/* 
 * File:   CANDriver..h
 * Author: itrpie
 *
 * Created on 21 settembre 2014, 16.54
 */
#include <p33FJ128MC706A.h>
#include <stdbool.h>


#ifndef CANDRIVER__H
#define	CANDRIVER__H

#define CAN_MSG_DATA	0x01 // message type
#define CAN_MSG_RTR	0x02 // data or RTR
#define CAN_FRAME_EXT	0x03 // Frame type
#define CAN_FRAME_STD	0x04 // extended or standard

/* CAN Baud Rate Configuration 		*/
#define FCAN  	40000000
#define BITRATE 1000000
#define NTQ 	20		// 20 Time Quanta in a Bit Time
#define BRP_VAL		((FCAN/(2*NTQ*BITRATE))-1) 

/* CAN Message Buffer Configuration */
#define  ECAN1_MSG_BUF_LENGTH 	4
typedef unsigned int ECAN1MSGBUF [ECAN1_MSG_BUF_LENGTH][8];
extern ECAN1MSGBUF  ecan1msgBuf __attribute__((space(dma)));

/* message structure in RAM */
typedef struct{
	/* keep track of the buffer status */
	unsigned char buffer_status;
	/* RTR message or data message */
	unsigned char message_type;
	/* frame type extended or standard */
	unsigned char frame_type;
	/* buffer being used to reference the message */
	unsigned int buffer;
	/* 29 bit id max of 0x1FFF FFFF
	*  11 bit id max of 0x7FF */
	unsigned long id;
	/* message data */
	unsigned int data[8];
	/* received message data length */
	unsigned int data_length;
}mID;


/* Function Prototype 	*/
void ecan1WriteRxAcptFilter(int n, long identifier, unsigned int exide,unsigned int bufPnt,unsigned int maskSel);
void ecan1WriteRxAcptMask(int m, long identifierMask, unsigned int mide,unsigned int exide);
void ecan1ClkInit(void);

void ecan1WriteTxMsgBufId(unsigned int buf, long txIdentifier, unsigned int ide, unsigned int remoteTransmit);
void ecan1WriteTxMsgBufData(unsigned int buf, unsigned int dataLength, unsigned int data1, unsigned int data2, unsigned int data3, unsigned int data4);
void ecan1WriteTxMsgBufDataStr(unsigned int buf, unsigned int dataLength, unsigned int* data);
void sendCanMessage(long identifier, unsigned int dataLength, unsigned int* data);

void ecan1DisableRXFilter(int n);
void ecan1Init(void);
void dma0Init(void);
void dma2Init(void);
void ecan1WriteMessage(void);

#endif	/* CANDRIVER__H */

