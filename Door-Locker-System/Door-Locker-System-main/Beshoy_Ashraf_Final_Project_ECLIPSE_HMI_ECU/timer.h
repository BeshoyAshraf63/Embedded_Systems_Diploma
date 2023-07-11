 /******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.h
 *
 * Description: header file for TIMER AVR driver
 *
 * Author: Beshoy Ashraf
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"







/*******************************************************************************
 *                             Types Declaration                               *
 *******************************************************************************/
typedef enum{
	OVF0=0x80, CTC0_DIS=0x88 , CTC0_TOGGLE=0x98 , CTC0_SET=0xB8 , CTC0_CLEAR=0xA8, FAST_PWM0_NON=0x68 ,FAST_PWM0_INV=0x78
}TIMER0_MODE;

typedef enum{
	STOP0=0,FCPUT0=1,FCPUT0_8=2,FCPUT0_64=3,FCPUT0_256=4,FCPUT0_1024=5,EXTERNAL_PIN_T0_FALLING=6,EXTERNAL_PIN_T0_RISING=7
}TIMER0_PRESCALER;

typedef enum{
	NO_INT0=0x00 ,OVF0_INT=0x01 , CTC0_INT=0x02
}TIMER0_INT_ENABLE;


typedef struct{
	TIMER0_MODE mode;
	TIMER0_PRESCALER  prescaler;
	TIMER0_INT_ENABLE intEnable0;
	uint8 TCNTValue;
	uint8 OCRValue;
}Timer0Setup;





typedef enum{
	OVF2=0x80, CTC2_DIS=0x88 , CTC2_TOGGLE=0x98 , CTC2_SET=0xB8 , CTC2_CLEAR=0xA8, FAST_PWM2_NON=0x68 ,FAST_PWM2_INV=0x78
}TIMER2_MODE;

typedef enum{
	STOP2=0,FCPUT2=1,FCPUT2_8=2,FCPUT2_32=3,FCPUT2_64=4,FCPUT2_128=5,FCPUT2_256=6,FCPUT2_1024=7
}TIMER2_PRESCALER;

typedef enum{
	NO_INT2=0x00 , OVF2_INT=0x40 , CTC2_INT=0x80
}TIMER2_INT_ENABLE;


typedef struct{
	TIMER2_MODE mode;
	TIMER2_PRESCALER  prescaler;
	TIMER2_INT_ENABLE intEnable2;
	uint8 TCNTValue;
	uint8 OCRValue;
}Timer2Setup;





typedef enum{
	OVF1A=0x08, CTC1A_DIS=0x08 , CTC1A_TOGGLE=0x48 , CTC1A_SET=0xC8 , CTC1A_CLEAR=0x88
}TIMER1_MODE_A;

typedef enum{
	OVF1B=0x00, CTC1B_DIS=0x08 , CTC1B_TOGGLE=0x08 , CTC1B_SET=0x08, CTC1B_CLEAR=0x08
}TIMER1_MODE_B;

typedef enum{
	STOP1=0,FCPUT1=1,FCPUT1_8=2,FCPUT1_64=3,FCPUT1_256=4,FCPUT1_1024=5,EXTERNAL_PIN_T1_FALLING=6,EXTERNAL_PIN_T1_RISING=7
}TIMER1_PRESCALER;

typedef enum{
	NO_INT1=0x00 ,OVF1_INT=0x04 , CTC1A_INT=0x10
}TIMER1_INT_ENABLE;


typedef struct{
	TIMER1_MODE_A modeA;
	TIMER1_MODE_B modeB;
	TIMER1_PRESCALER  prescaler;
	TIMER1_INT_ENABLE intEnable1;
	uint16 TCNTValue;
	uint16 OCRValue;
}Timer1Setup;




/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description: Function to initialize Timer0 of AVR.
 */
void Timer0_Start(const Timer0Setup * Config_Ptr);


/*
 * Description: Function to initialize Timer1 of AVR.
 */
void Timer1_Start(const Timer1Setup * Config_Ptr);


/*
 * Description: Function to initialize Timer2 of AVR.
 */
void Timer2_Start(const Timer2Setup * Config_Ptr);


/*
 * Description: Function to set the Call Back function address.
 */
void Timer0_setCallBack(void(*a_ptr)(void));


/*
 * Description: Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void));


/*
 * Description: Function to set the Call Back function address.
 */
void Timer2_setCallBack(void(*a_ptr)(void));


/*
 * Description: Function to change clock of timer0.
 */
void Timer0_setClock(uint8 clock );


/*
 * Description: Function to change clock of timer1.
 */
void Timer1_setClock(uint8 clock );


/*
 * Description: Function to change clock of timer2.
 */
void Timer2_setClock(uint8 clock );


/*
 * Description: Function to change compare value of timer0.
 */
void Timer0_setCTC(uint8 ctc );


/*
 * Description: Function to change compare value of timer1.
 */
void Timer1_setCTC(uint16 ctc );


/*
 * Description: Function to change compare value of timer2.
 */
void Timer2_setCTC(uint8 ctc );



/*
 * Description: Function to stop Timer0 of AVR after done.
 */
void Timer0_DeInit();


/*
 * Description: Function to stop Timer1 of AVR after done.
 */
void Timer1_DeInit();


/*
 * Description: Function to stop Timer2 of AVR after done.
 */
void Timer2_DeInit();

#endif /* TIMER_H_ */
