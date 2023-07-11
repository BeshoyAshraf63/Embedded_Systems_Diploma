 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: header file for PWM AVR driver
 *
 * Author: Beshoy Ashraf
 *
 *******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"


/*******************************************************************************
 *                             Types Declaration                               *
 *******************************************************************************/
typedef enum{
	STOP0=0,FCPU0=1,FCPU0_8=2,FCPU0_64=3,FCPU0_256=4,FCPU0_1024=5,EXTERNAL_PIN_T0_FALLING=6,EXTERNAL_PIN_T0_RISING=7
}TIMER0_Prescaler;

typedef enum{
	NON_INVERTING0=0x20 ,INVERTING0=0x30
}PWM0_Mode;




typedef enum{
	STOP2=0,FCPU2=1,FCPU2_8=2,FCPU2_32=3,FCPU2_64=4,FCPU2_128=5,FCPU2_256=6,FCPU2_1024=7
}TIMER2_Prescaler;

typedef enum{
	NON_INVERTING2=0x20 ,INVERTING2=0x30
}PWM2_Mode;



typedef struct{
	TIMER0_Prescaler prescaler;
	uint8 dutyCycle;
	PWM0_Mode mode;
}PWM0_ConfigType;



typedef struct{
	TIMER2_Prescaler prescaler;
	uint8 dutyCycle;
	PWM2_Mode mode;
}PWM2_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description: Function to initialize PWM of timer Timer0 of AVR.
 */
void PWM_Timer0_Start(const PWM0_ConfigType *Config_Ptr);

/*
 * Description: Function to initialize PWM of timer Timer2 of AVR.
 */
void PWM_Timer2_Start(const PWM2_ConfigType *Config_Ptr);

/*
 * Description: Function to de-initialize PWM of timer Timer0 of AVR.
 */
void PWM_Timer0_DeInit(void);

/*
 * Description: Function to de-initialize PWM of timer Timer2 of AVR.
 */
void PWM_Timer2_DeInit(void);

/*
 * Description: Function to change duty cycle of PWM of timer Timer2 of AVR.
 */
void PWM_Timer0_changeDuty(uint8 duty);

/*
 * Description: Function to change duty cycle of PWM of timer Timer2 of AVR.
 */
void PWM_Timer2_changeDuty(uint8 duty);

/*
 * Description: Function to change clock Timer0 of AVR.
 */
void PWM_Timer0_changeClock(TIMER0_Prescaler clock);

/*
 * Description: Function to change clock Timer2 of AVR.
 */
void PWM_Timer2_changeClock(TIMER2_Prescaler clock);

#endif /* PWM_H_ */
