 /******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the BUZZER driver
 *
 * Author: Beshoy Ashraf
 *
 *******************************************************************************/

#include "gpio.h"
#include "buzzer.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * Initialize the buzzer pin.
 */
void BUZZER_init(void){
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);
}


/*
 * Description :
 * Turns on the buzzer.
 */
void BUZZER_on(void){
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,1);
}


/*
 * Description :
 * Turns off the buzzer.
 */
void BUZZER_off(void){
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,0);
}
