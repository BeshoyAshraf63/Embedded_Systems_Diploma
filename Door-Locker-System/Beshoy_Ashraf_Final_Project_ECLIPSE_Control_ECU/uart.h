 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"


/*******************************************************************************
 *                             Types Declaration                               *
 *******************************************************************************/
typedef enum{
	FIVE_BITS=0x00 , SIX_BITS=0x02 , SEVEN_BITS=0x04 , EIGHT_BITS=0x06
}Frame_Shape;


typedef enum{
	DISABLED=0x00 , EVEN=0x20 , ODD=0x30
}Parity;


typedef enum{
	ONE=0x00 ,TWO=0x08
}Stop_Bits;


typedef struct{
	Frame_Shape size;
	Parity parity;
	Stop_Bits stop;
	uint32 baudRate;
}UART_Config;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_Config *Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
