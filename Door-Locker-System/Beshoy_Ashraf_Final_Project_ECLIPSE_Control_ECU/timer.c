 /******************************************************************************
 *
 * Module: TIMER
 *
 * File Name: timer.c
 *
 * Description: Source file for TIMER AVR driver
 *
 * Author: Beshoy Ashraf
 *
 *******************************************************************************/

#include "timer.h"
#include "avr/io.h" /* To use the IO Ports Registers */
#include <avr/interrupt.h> /* For Timer ISR */


/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/
/* Global variables to hold the address of the call back function in the application of timer0 */
static volatile void (*g_callBackPtr0)(void) = NULL_PTR;
/* Global variables to hold the address of the call back function in the application of timer1*/
static volatile void (*g_callBackPtr1)(void) = NULL_PTR;
/* Global variables to hold the address of the call back function in the application of timer2*/
static volatile void (*g_callBackPtr2)(void) = NULL_PTR;




/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/
ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the interrupt is detected */
		(*g_callBackPtr0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}


ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the interrupt is detected */
		(*g_callBackPtr0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}




ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the interrupt is detected */
		(*g_callBackPtr1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}


ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the interrupt is detected */
		(*g_callBackPtr1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}





ISR(TIMER2_OVF_vect)
{
	if(g_callBackPtr2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the interrupt is detected */
		(*g_callBackPtr2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}


ISR(TIMER2_COMP_vect)
{
	if(g_callBackPtr2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the interrupt is detected */
		(*g_callBackPtr2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}




/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description: Function to initialize Timer0 of AVR.
 */
void Timer0_Start(const Timer0Setup * Config_Ptr)
{
	/* TCCR0 Register Bits Description:
	 * FOC0 = 1 (when PWM mode is disabled) (set auto with Config_Ptr->mode)
	 * WGM01:0  to choose mode of timer (CTC-PWM(fast)-OVF).
	 * COM01:0  to choose mode of CTC mode.
	 * CS02:0   to choose clock and prescaler of timer0.
	 */
	TCCR0 |= (Config_Ptr->mode) | (Config_Ptr->prescaler) ;
	TCNT0  = (Config_Ptr->TCNTValue);
	OCR0   = (Config_Ptr->OCRValue);
	/* TIMSK Register Bits Description:
	 * TOIE0    = 1 Enable interrupt request for timer0 OVF mode.
	 * OCIE0    = 1 Enable interrupt request for timer0 CTC mode.
	 */
	TIMSK = (Config_Ptr->intEnable0);
}




/*
 * Description: Function to initialize Timer2 of AVR.
 */
void Timer1_Start(const Timer1Setup * Config_Ptr)
{
	/* TCCR2 Register Bits Description:
	 * FOC1A = 1 (when PWM mode is disabled) (set auto with Config_Ptr->mode)
	 * FOC1B = 1 (when PWM mode is disabled) (set auto with Config_Ptr->mode)
	 * WGM13:0  to choose mode of timer (CTC-PWM(fast)-OVF).
	 * COM1A1/COM1B1:0  to choose mode of CTC mode.
	 * CS12:0   to choose clock and prescaler of timer0.
	 */
	TCCR1A |= (Config_Ptr->modeA)  ;
	TCCR1B |= (Config_Ptr->modeB) | (Config_Ptr->prescaler) ;
	TCNT1   = (Config_Ptr->TCNTValue);
	OCR1A   = (Config_Ptr->OCRValue);
	/* TIMSK Register Bits Description:
	 * TOIE1    = 1 Enable interrupt request for timer1 OVF mode.
	 * OCIE1A   = 1 Enable interrupt request for timer1-(channel A) CTC mode.
	 * OCIE1B   = 1 Enable interrupt request for timer1-(channel B) CTC mode (Needed PWM mode/ Not supported here).
	 * OCIE2    = 1 Enable interrupt request for timer2 CTC mode.
	 */
	TIMSK = (Config_Ptr->intEnable1);
}




/*
 * Description: Function to initialize Timer2 of AVR.
 */
void Timer2_Start(const Timer2Setup * Config_Ptr)
{
	/* TCCR2 Register Bits Description:
	 * FOC2 = 1 (when PWM mode is disabled) (set auto with Config_Ptr->mode)
	 * WGM21:0  to choose mode of timer (CTC-PWM(fast)-OVF).
	 * COM21:0  to choose mode of PWM mode or CTC mode.
	 * CS22:0   to choose clock and prescaler of timer0.
	 */
	TCCR2 |= (Config_Ptr->mode) | (Config_Ptr->prescaler) ;
	TCNT2 = (Config_Ptr->TCNTValue);
	OCR2  = (Config_Ptr->OCRValue);
	/* TIMSK Register Bits Description:
	 * TOIE2    = 1 Enable interrupt request for timer2 OVF mode.
	 * OCIE2    = 1 Enable interrupt request for timer2 CTC mode.
	 */
	TIMSK = (Config_Ptr->intEnable2);
}




/*
 * Description: Function to change clock of timer0.
 */
void Timer0_setClock(uint8 clock ){
	TCCR0 |= ((TCCR0 & 0xF8) | clock);
}




/*
 * Description: Function to change clock of timer1.
 */
void Timer1_setClock(uint8 clock ){
	TCCR1B |= ((TCCR1B & 0xF8) | clock);
}



/*
 * Description: Function to change clock of timer2.
 */
void Timer2_setClock(uint8 clock ){
	TCCR2 |= ((TCCR2 & 0xF8) | clock);
}



/*
 * Description: Function to change compare value of timer0.
 */
void Timer0_setCTC(uint8 ctc ){
	TCNT0=0;
	OCR0=ctc;
}




/*
 * Description: Function to change compare value of timer1.
 */
void Timer1_setCTC(uint16 ctc ){
	TCNT1=0;
	OCR1A=ctc;
}



/*
 * Description: Function to change compare value of timer2.
 */
void Timer2_setCTC(uint8 ctc ){
	TCNT2=0;
	OCR2=ctc;
}




/*
 * Description: Function to stop Timer2 of AVR after done.
 */
void Timer0_DeInit(){
	TCCR0=0;
	OCR0=0;
	TIMSK &= ~(1<<OCIE0);
	TIMSK &= ~(1<<TOIE0);
}



/*
 * Description: Function to stop Timer2 of AVR after done.
 */
void Timer1_DeInit(){
	TCCR1A=0;
	TCCR1B=0;
	OCR1A=0;
	TCNT1=0;
	TIMSK &= ~(1<<OCIE1A);
	TIMSK &= ~(1<<TOIE1);
}




/*
 * Description: Function to stop Timer2 of AVR after done.
 */
void Timer2_DeInit(){
	TCCR2=0;
	OCR2=0;
	TIMSK &= ~(1<<OCIE2);
	TIMSK &= ~(1<<TOIE2);
}




/*
 * Description: Function to set the Call Back function address.
 */
void Timer0_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr0 = a_ptr;
}




/*
 * Description: Function to set the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr1 = a_ptr;
}




/*
 * Description: Function to set the Call Back function address.
 */
void Timer2_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr2 = a_ptr;
}



