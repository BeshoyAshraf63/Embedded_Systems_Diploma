 /******************************************************************************
 *
 * Module: DcMotor
 *
 * File Name: dcmotor.c
 *
 * Description: Source file for DcMotor driver
 *
 * Author: Beshoy Ashraf
 *
 *******************************************************************************/
#include "dcmotor.h"
#include "pwm.h"
#include "gpio.h"


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description: Function to initialize Dc-Motor connected to AVR.
 */
void DcMotor_init(void){
	/* Input1 pin of the first motor */
	GPIO_setupPinDirection(MOTOR_INPUT0_PORT_ID, MOTOR_INPUTA_PIN_ID , PIN_OUTPUT);
	/* Input2 pin of the first motor */
	GPIO_setupPinDirection(MOTOR_INPUT0_PORT_ID, MOTOR_INPUTB_PIN_ID , PIN_OUTPUT);
	/* Enable pin of the first motor */
	GPIO_setupPinDirection(MOTOR_ENABLE0_PORT_ID, MOTOR_ENABLE0_PIN_ID , PIN_OUTPUT);
	/* Initialize speed of motor =0 at first */
	GPIO_writePin(MOTOR_INPUT0_PORT_ID, MOTOR_INPUTA_PIN_ID ,0);
	GPIO_writePin(MOTOR_INPUT0_PORT_ID, MOTOR_INPUTB_PIN_ID ,0);


	/* Input1 pin of the second motor */
	GPIO_setupPinDirection(MOTOR_INPUT1_PORT_ID, MOTOR_INPUTC_PIN_ID , PIN_OUTPUT);
	/* Input2 pin of the second motor */
	GPIO_setupPinDirection(MOTOR_INPUT1_PORT_ID, MOTOR_INPUTD_PIN_ID , PIN_OUTPUT);
	/* Enable pin of the second motor */
	GPIO_setupPinDirection(MOTOR_ENABLE1_PORT_ID, MOTOR_ENABLE1_PIN_ID , PIN_OUTPUT);
	/* Initialize speed of motor =0 at first */
	GPIO_writePin(MOTOR_INPUT1_PORT_ID, MOTOR_INPUTC_PIN_ID ,0);
	GPIO_writePin(MOTOR_INPUT1_PORT_ID, MOTOR_INPUTD_PIN_ID ,0);
}



/*
 * Description: Function to initialize Dc Motor rotation connected to PWM Timer0 of AVR.
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed){
	uint8 value1,value2;
	/* Start pwm mode of timer0 to control speed of motor at pin OC0/PB3 */
	PWM0_ConfigType s_config={FCPU0_8 , speed , NON_INVERTING0};
	PWM_Timer0_Start(&s_config);

	/* Configure State of Motor CW/ACW */
	value1= (0x01 & state);
	value2= ((0x02 & state)>>1);
	GPIO_writePin(MOTOR_INPUT0_PORT_ID, MOTOR_INPUTA_PIN_ID , value1);
	GPIO_writePin(MOTOR_INPUT0_PORT_ID, MOTOR_INPUTB_PIN_ID , value2);
}



/*
 * Description: Function to initialize Dc Motor rotation connected to PWM Timer2 of AVR.
 */
void DcMotor_Rotate2(DcMotor_State state, uint8 speed){
	uint8 value1,value2;;
	/* Start pwm mode of timer0 to control speed of motor at pin OC0/PB3 */
	PWM2_ConfigType s_config={FCPU2_8, speed ,NON_INVERTING2};
	PWM_Timer2_Start(&s_config);

	/* Configure State of Motor CW/ACW */
	value1= (0x01 & state);
	value2= ((0x02 & state)>>1);
	GPIO_writePin(MOTOR_INPUT1_PORT_ID, MOTOR_INPUTC_PIN_ID , value1);
	GPIO_writePin(MOTOR_INPUT1_PORT_ID, MOTOR_INPUTD_PIN_ID , value2);
}



/*
 * Description: Function to change speed of Dc Motor rotation connected to PWM Timer1 of AVR.
 */
void DcMotor_setSpeed(uint8 speed){
	PWM_Timer0_changeDuty(speed);
}



/*
 * Description: Function to change speed of Dc Motor rotation connected to PWM Timer2 of AVR.
 */
void DcMotor_setSpeed2(uint8 speed){
	PWM_Timer2_changeDuty(speed);
}



/*
 * Description: Function to stop Dc Motor rotation connected to PWM Timer1 of AVR.
 */
void DcMotor_stopMotor(void){
	/* Best Method:
	 * As it stops PWM signal as well to conserve Power Consumption.
	 *  */
	PWM_Timer0_DeInit();

	/* Another Method:
	 * Using motor input pins write logical 0 to both
	 * GPIO_writePin(MOTOR_INPUT0_PORT_ID, MOTOR_INPUTC_PIN_ID ,LOGIC_LOW);
	 * GPIO_writePin(MOTOR_INPUT0_PORT_ID, MOTOR_INPUTB_PIN_ID ,LOGIC_HIGH);
	 * */

	/* Another Method:
	 * can be done by stopping the PWM clock :
	 * PWM_Timer0_changeClock(STOP0);
	 */
}



/*
 * Description: Function to stop Dc Motor rotation connected to PWM Timer2 of AVR.
 */
void DcMotor_stopMotor2(void){
	/* Best Method:
	 * As it stops PWM signal as well to conserve Power Consumption.
	 *  */
	PWM_Timer2_DeInit();

	/* Another Method:
	 * Using motor input pins write logical 0 to both
	 * GPIO_writePin(MOTOR_INPUT1_PORT_ID, MOTOR_INPUTC_PIN_ID ,LOGIC_LOW);
	 * GPIO_writePin(MOTOR_INPUT1_PORT_ID, MOTOR_INPUTD_PIN_ID ,LOGIC_HIGH);
	 * */

	/* Another Method:
	 * can be done by stopping the PWM clock :
	 * PWM_Timer2_changeClock(STOP2);
	 */
}
