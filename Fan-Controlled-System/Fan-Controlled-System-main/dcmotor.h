 /******************************************************************************
 *
 * Module: DcMotor
 *
 * File Name: dcmotor.h
 *
 * Description: Header file for DcMotor driver
 *
 * Author: Beshoy Ashraf
 *
 *******************************************************************************/


#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"


/*******************************************************************************
 *                             Types Declaration                               *
 *******************************************************************************/
typedef enum{
	STOP=0x00 ,CLOCK_WISE=0x02  , ANTI_CLOCK_WISE=0x01
}DcMotor_State ;



/*******************************************************************************
 *                                 Definitions                                 *
 *******************************************************************************/
/* First motor (OC0) */
#define MOTOR_INPUTA_PIN_ID       PIN0_ID
#define MOTOR_INPUTB_PIN_ID       PIN1_ID
#define MOTOR_INPUT0_PORT_ID      PORTB_ID

#define MOTOR_ENABLE0_PORT_ID     PORTB_ID
#define MOTOR_ENABLE0_PIN_ID      PIN3_ID /*OC0*/

/* Second motor (OC2) */
#define MOTOR_INPUTC_PIN_ID       PIN2_ID
#define MOTOR_INPUTD_PIN_ID       PIN3_ID
#define MOTOR_INPUT1_PORT_ID      PORTB_ID

#define MOTOR_ENABLE1_PORT_ID     PORTD_ID
#define MOTOR_ENABLE1_PIN_ID      PIN7_ID /*OC2*/



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description: Function to initialize Dc-Motor connected to AVR.
 */
void DcMotor_init(void);

/*
 * Description: Function to initialize Dc Motor rotation connected to PWM Timer0 of AVR.
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed);

/*
 * Description: Function to initialize Dc Motor rotation connected to PWM Timer2 of AVR.
 */
void DcMotor_Rotate2(DcMotor_State state, uint8 speed);

/*
 * Description: Function to change speed of Dc Motor rotation connected to PWM Timer2 of AVR.
 */
void DcMotor_setSpeed(uint8 speed);

/*
 * Description: Function to change speed of Dc Motor rotation connected to PWM Timer2 of AVR.
 */
void DcMotor_setSpeed2(uint8 speed);

/*
 * Description: Function to stop Dc Motor rotation connected to PWM Timer1 of AVR.
 */
void DcMotor_stopMotor(void);

/*
 * Description: Function to stop Dc Motor rotation connected to PWM Timer2 of AVR.
 */
void DcMotor_stopMotor2(void);



#endif /* DCMOTOR_H_ */
