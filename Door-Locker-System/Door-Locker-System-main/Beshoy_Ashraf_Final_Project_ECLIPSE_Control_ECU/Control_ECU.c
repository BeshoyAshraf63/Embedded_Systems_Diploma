/*
 ============================================================================
 Name        : Control_ECU.c
 Author      : Beshoy Ashraf
 Description : Control ECU main file
 Date        : 10/24/2021
 ============================================================================
 */

#include "dcmotor.h"
#include "timer.h"
#include "uart.h"
#include <util/delay.h>
#include "UART_msgs.h"
#include "buzzer.h"
#include "avr/io.h" /* To enable global interrupt bit */


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
/* Global array to store user password for first time */
uint8 password1[5];

/* Global array to store user password for second time */
uint8 password2[5];

/* Global array to store user password for third time */
uint8 password3[5];

/* Global array to store user password from EEPROM */
uint8 EEPROM_password[5];

/* Global variable to count how many wrong passwords entered */
uint8  volatile g_mismatch=0;

/* Global variable to store UART order from the other controller */
uint8  volatile g_order;

/* Global variable to count */
uint8  volatile g_tick1=0;

/* Global variable to count */
uint16 volatile g_tick2=0;

/* Global variable to count */
uint16 volatile g_tick3=0;

/*******************************************************************************
 *                         Functions Prototypes                                *
 *******************************************************************************/
/*
 * Description :
 * read password from inside EEPROM and save it in global variable.
 * Inputs: array.
 * Outputs: None.
 */
void EEPROM_readPassword (uint8 *ptr);

/*
 * Description :
 * Saves password inside EEPROM.
 * Inputs: array.
 * Outputs: None.
 */
void EEPROM_writePassword (uint8 *ptr);

/*
 * Description :
 * Increment the three global variables.
 */
void Timer_Count();

/*
 * Description :
 * Takes two arrays and compare them.
 * Inputs: Two arrays.
 * Outputs: Number of errors.
 */
uint8 ComparePasswords(uint8 *ptr1, uint8 *ptr2);

/*
 * Description :
 * Save the password sent from HMI MC in case of openDoor/ChangePassword scenarios.
 * Save it inside a global array.
 * Inputs: None.
 * Outputs: None.
 */
void saveRequestedPassword(void);

/*
 * Description :
 * Save the password sent from HMI MC in case of NewPassword/ChangePassword scenarios.
 * Save it inside a global array.
 * Inputs: None.
 * Outputs: None.
 */
void saveNewPassword(void);
/*******************************************************************************
 *                         Functions Definitions                               *
 *******************************************************************************/
/*
 * Description :
 * Save the password sent from HMI MC in case of NewPassword/ChangePassword scenarios.
 * Save it inside a global array.
 * Inputs: None.
 * Outputs: None.
 */
void saveNewPassword(void){
	uint8 i;
	for(i=0;i<PasswordSize;i++)
	{
		password1[i]=UART_recieveByte();
	}


	for(i=0;i<PasswordSize;i++)
	{
		password2[i]=UART_recieveByte();
	}

}


/*
 * Description :
 * Save the password sent from HMI MC in case of openDoor/ChangePassword scenarios.
 * Save it inside a global array.
 * Inputs: None.
 * Outputs: None.
 */
void saveRequestedPassword(void){
	uint8 i;
	for(i=0;i<PasswordSize;i++)
	{
		password3[i]=UART_recieveByte();
	}
}


/*
 * Description :
 * Takes two arrays and compare them.
 * Inputs: Two arrays.
 * Outputs: Number of errors.
 */
uint8 ComparePasswords(uint8 *ptr1, uint8 *ptr2){
	uint8 i, error_count=0;
	for(i=0;i<PasswordSize;i++){
		if(ptr1[i] != ptr2[i])
		{
			error_count++;
		}
	}
	return error_count;
}


/*
 * Description :
 * Increment the three global variables.
 */
void Timer_Count(){
	g_tick2++;
	g_tick1++;
	g_tick3++;
}


/*
 * Description :
 * Saves password inside EEPROM.
 * Inputs: array.
 * Outputs: None.
 */
void EEPROM_writePassword (uint8 *ptr) {
	uint8 i;
	for(i=0 ; i<PasswordSize ; i++)
	{
		EEPROM_writeByte((EEPROM_Address+i), ptr[i]);
		_delay_ms(10);
	}
}


/*
 * Description :
 * read password from inside EEPROM and save it in global variable.
 * Inputs: array.
 * Outputs: None.
 */
void EEPROM_readPassword (uint8 *ptr) {
	uint8 i;
	for(i=0 ; i<15 ; i++)
		for(i=0 ; i<15 ; i++)
		{
			EEPROM_readByte((EEPROM_Address+i), &ptr[i]);
			_delay_ms(10);
		}
}

int main(void){
	/* Enable global interrupt bit for the timer */
	SREG |= (1<<7);

	/* Initialize the UART driver with:
	 * 8 bit data mode
	 * One stop bit
	 * No parity bit
	 * Baud-rate = 9600 bits/sec
	*/
	UART_Config s_UARTconfig={EIGHT_BITS,DISABLED,ONE,9600};
	UART_init(&s_UARTconfig);

	/* Initialize the TWI/I2C Driver */
	EEPROM_init();

	/* Initialize the Dc-motor Driver */
	DcMotor_init();

	/* Initialize the Buzzer Driver */
	BUZZER_init();

	/* Wait until MC1 is ready */
	while(UART_recieveByte() != MC1_READY){}
	UART_sendByte(MC2_READY);

	UART_sendByte(getNewPassword);

	while(1){
		g_order=UART_recieveByte();

		switch(g_order)
		{

		case HMI_PasswordReady :
			g_order=0;
			saveNewPassword();
			if(((ComparePasswords(password1,password2)) ==0))
			{
				//code to store data inside eeprom
				EEPROM_writePassword(password2);
				UART_sendByte(PasswordMatch );
			}
			else
			{
				UART_sendByte(passwordsUnmatched);
			}
			break;


		/* */
		case HMI_RequestedPasswordReady :
			g_order=0;
			saveRequestedPassword();
			EEPROM_readPassword(EEPROM_password);

			_delay_ms(50);

			if((ComparePasswords(EEPROM_password,password3)) ==0)
			{
				UART_sendByte(RequestedCorrectPassword );
				g_mismatch=0;
			}

			else
			{
				g_mismatch++;
				UART_sendByte(RequestedINCorrectPassword);
				_delay_ms(500);

			}

			if(g_mismatch==3)
			{
				/* Initialize the Timer0 driver with:
				 * Normal (OVF) mode.
				 * F_CPU/1024 prescaler.
				 * Interrupt mode.
				 * starting value = 0.
				 * Setting callBackFunction with Timer_Count();.
				*/
				Timer0Setup s_Timer0config={OVF0,FCPUT0_1024,OVF0_INT,0,0};
				Timer0_Start(&s_Timer0config);
				Timer0_setCallBack(Timer_Count);

				UART_sendByte(errorScreen);

				g_mismatch=0;

				BUZZER_on();
				g_tick3=0;

				while(g_tick3 != 1780);
				BUZZER_off();

				/* Stops timer2 */
				Timer0_DeInit();
			}
		    break;


		/* */
		case openDoor :

			g_order=0;

			/* Initialize the Timer2 driver with:
			 * Normal (OVF) mode.
			 * F_CPU/1024 prescaler.
			 * Interrupt mode.
			 * starting value = 0.
			 * Setting callBackFunction with Timer_Count();.
			 * Note: we could have used only one timer (timer0) but i used (timer2) too
			 * to make sure that whole driver is working well.
			*/
			Timer2Setup s_Timer0config={OVF2,FCPUT2_1024,OVF2_INT,0,0};
			Timer2_Start(&s_Timer0config);
			Timer2_setCallBack(Timer_Count);
			UART_sendByte(DoorOpening);

			DcMotor_Rotate(CLOCK_WISE,100);
			g_tick2=0;
			while(g_tick2 != 445);

			UART_sendByte(DoorIsOpened);
			DcMotor_Rotate(CLOCK_WISE,0);
			g_tick1=0;
			while(g_tick1 != 95);



			UART_sendByte(DoorClosing);
			DcMotor_Rotate(ANTI_CLOCK_WISE,100);
			g_tick2=0;
			while(((g_tick2) != (445)));

			UART_sendByte(DoorIsClosed);
			DcMotor_Rotate(CLOCK_WISE,0);

			_delay_ms(2000);

			UART_sendByte(PasswordMatch);

			/* Stops timer2 */
			Timer2_DeInit();
			break;


		/* */
		default :
			g_order=0;
			break;
		}
	}
}
