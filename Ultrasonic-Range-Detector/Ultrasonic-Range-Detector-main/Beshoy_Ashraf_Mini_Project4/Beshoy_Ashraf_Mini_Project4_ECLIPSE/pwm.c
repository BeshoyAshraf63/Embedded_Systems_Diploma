 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: Source file for PWM AVR driver
 *
 * Author: Beshoy Ashraf
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the IO Ports Registers */
#include "pwm.h"


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description: Function to initialize PWM Timer0 of AVR.
 */
void PWM_Timer0_Start(const PWM0_ConfigType *Config_Ptr){
/*
 * Description:
 * 1. WGM01:0 =1 to work with fast PWM mode of TIMER0 of AVR.
 * 2. FOC0 =0 to work with fast PWM mode of TIMER0 of AVR.
 * 3. CS02:00 are set with the entered pre-scaler.
 * 4. COM01:00 are set with required mode of PWM (inverting/non-inverting).
 */
	TCCR0 = ( (1<<WGM00) | (1<<WGM01) | (Config_Ptr->prescaler) | (Config_Ptr->mode) );
	TCNT0 =0; /* Reseting TIMER0 register */

	/* A simple equation to calculate OCR0 value depending on preferred duty cycle entered. */
	OCR0 = 255*((float)(Config_Ptr->dutyCycle)/100);

	/* Configure PB3/OC0 as output pin --> pin where the PWM signal is generated from MC. */
	DDRB = DDRB | (1<<PB3);
}



/*
 * Description: Function to initialize PWM of Timer2 of AVR.
 */
void PWM_Timer2_Start(const PWM2_ConfigType *Config_Ptr){
/*
 * Description:
 * 1. WGM21:0 =1 to work with fast PWM mode of TIMER0 of AVR.
 * 2. FOC2 =0 to work with fast PWM mode of TIMER0 of AVR.
 * 3. CS22:00 are set with the entered pre-scaler.
 * 4. COM21:00 are set with required mode of PWM (inverting/non-inverting).
 */
	TCCR2 = ( (1<<WGM20) | (1<<WGM21) | (Config_Ptr->prescaler) | (Config_Ptr->mode) );
	TCNT2 =0; /* Reseting TIMER0 register */

	/* A simple equation to calculate OCR0 value depending on preferred duty cycle entered. */
	OCR2 = 255*((float)(Config_Ptr->dutyCycle)/100);

	/* Configure PD7/OC2 as output pin --> pin where the PWM signal is generated from MC. */
	DDRD = DDRD | (1<<PD7);
}



/*
 * Description: Function to de-initialize PWM of Timer0 of AVR.
 */
void PWM_Timer0_DeInit(void){
	TCCR0=0;
	TCNT0=0;
	OCR0=0;
}



/*
 * Description: Function to de-initialize PWM of Timer2 of AVR.
 */
void PWM_Timer2_DeInit(void){
	TCCR2=0;
	TCNT2=0;
	OCR2=0;
}



/*
 * Description: Function to change duty cycle of PWM of Timer2 of AVR.
 */
void PWM_Timer0_changeDuty(uint8 duty){
	/* A simple equation to calculate OCR0 value depending on preferred duty cycle entered. */
	OCR0 = 255*((float)duty/100);
	TCNT0=0;
}



/*
 * Description: Function to change duty cycle of PWM of Timer2 of AVR.
 */
void PWM_Timer2_changeDuty(uint8 duty){
	/* A simple equation to calculate OCR0 value depending on preferred duty cycle entered. */
	OCR2 = 255*((float)duty/100);
	TCNT2=0;
}



/*
 * Description: Function to change clock Timer0 of AVR.
 */
void PWM_Timer0_changeClock(TIMER0_Prescaler clock){
	TCCR0 = (TCCR0 & 0xF8) | clock;
}



/*
 * Description: Function to change clock Timer2 of AVR.
 */
void PWM_Timer2_changeClock(TIMER2_Prescaler clock){
	TCCR2 = (TCCR2 & 0xF8) | clock;
}
