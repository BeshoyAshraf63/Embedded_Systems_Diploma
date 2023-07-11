 /******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.h
 *
 * Description: header file for the BUZZER driver
 *
 * Author: Beshoy Ashraf
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_


/*******************************************************************************
 *                             Definitions                                    *
 *******************************************************************************/
#define BUZZER_PIN_ID       PIN5_ID
#define BUZZER_PORT_ID      PORTC_ID

/*******************************************************************************
 *                         Functions Prototypes                                *
 *******************************************************************************/
/*
 * Description :
 * Initialize the buzzer pin.
 */
void BUZZER_init(void);

/*
 * Description :
 * Turns on the buzzer.
 */
void BUZZER_on(void);

/*
 * Description :
 * Turns off the buzzer.
 */
void BUZZER_off(void);


#endif /* BUZZER_H_ */
