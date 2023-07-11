/*
 ============================================================================
 Name        : HMI.c
 Author      : Beshoy Ashraf
 Description : HMI MCU main file
 Date        : 10/24/2021
 ============================================================================
 */

#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include <util/delay.h>
#include "UART_msgs.h"
#include "timer.h"
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

/* Global variable to store UART order from the other controller */
uint8 volatile g_order=0;

/* Global variable to store keypressed from user */
uint8 volatile g_key;

/* Global variable incremented by timer setcallback function */
uint16 volatile g_tick=0;

/* Global flag */
uint16 volatile g_flag=0;
/*******************************************************************************
 *                         Functions Prototypes                                *
 *******************************************************************************/
/*
 * Description :
 * Takes the password from user in case of openDoor/ChangePassword scenarios.
 * Save it inside a global array.
 * Inputs: None.
 * Outputs: None.
 */
void requestPassword(void);

/*
 * Description :
 * Display main menu to user.
 * Inputs: None.
 * Outputs: None.
 */
void mainOptions(void);

/*
 * Description :
 * Takes the New password from user in case of first time of by choice of user.
 * Saves the two password inside two global arrays.
 * Inputs: None.
 * Outputs: None.
 */
void getUserNewPassword(void);

/*
 * Description :
 * Sends the two password entered by user to check it in second controller.
 * Save it inside a global array.
 * Inputs: None.
 * Outputs: None.
 */
void sendRequestedPassword(void);

/*
 * Description :
 * SetCallBack function that increments the g_tick global variable.
 */
void Timer_Count();


/*******************************************************************************
 *                         Functions Definitions                               *
 *******************************************************************************/
/*
 * Description :
 * Takes the New password from user in case of first time of by choice of user.
 * Saves the two password inside two global arrays.
 * Inputs: None.
 * Outputs: None.
 */
void getUserNewPassword(void){
	uint8 i;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Enter new pass!");
	LCD_moveCursor(1,0);
	for(i=0;i<PasswordSize;i++)
	{
		password1[i]=KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		_delay_ms(350);
	}

	_delay_ms(350);

	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Renter new pass!");
	LCD_moveCursor(1,0);
	for(i=0;i<PasswordSize;i++)
	{
		password2[i]=KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		_delay_ms(350);
	}


}


/*
 * Description :
 * Takes the password from user in case of openDoor/ChangePassword scenarios.
 * Save it inside a global array.
 * Inputs: None.
 * Outputs: None.
 */
void requestPassword(void){
	uint8 i;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Enter old pass!");
	LCD_moveCursor(1,0);
	for(i=0;i<PasswordSize;i++)
	{
		password3[i]=KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		_delay_ms(350);
	}
}


/*
 * Description :
 * Sends the two password entered by user to check it in second controller.
 * Save it inside a global array.
 * Inputs: None.
 * Outputs: None.
 */
void sendRequestedPassword(void){
	uint8 i;
	for(i=0;i<PasswordSize;i++)
	{
		UART_sendByte(password3[i]);
	}
}


/*
 * Description :
 * Display main menu to user.
 * Inputs: None.
 * Outputs: None.
 */
void mainOptions(void){
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"+ :open door") ;
	LCD_displayStringRowColumn(1,0,"- :change pass");
	g_key=KEYPAD_getPressedKey();
	_delay_ms(350);
	if (g_key =='+')
	{
		LCD_clearScreen();
		requestPassword();
		/*Tell the other MC2 that requested password is ready*/
		UART_sendByte(HMI_RequestedPasswordReady);
		sendRequestedPassword();
	}
	else if(g_key == '-')
	{
		LCD_clearScreen();
		requestPassword();
		/*Tell the other MC2 that requested password is ready*/
		UART_sendByte(HMI_RequestedPasswordReady);
		sendRequestedPassword();
	}
}


/*
 * Description :
 * Sends the two password entered by user in case of firstTimePasswords/ChangePassword scenarios to second controller.
 * Save it inside a global array.
 * Inputs: None.
 * Outputs: None.
 */
void sendUserNewPassword(void){
	uint8 i;
	for(i=0;i<PasswordSize;i++)
	{
		UART_sendByte(password1[i]);
	}


	for(i=0;i<PasswordSize;i++)
	{
		UART_sendByte(password2[i]);
	}
}


/*
 * Description :
 * SetCallBack function that increments the g_tick global variable.
 */
void Timer_Count(){
	g_tick++;
}


int main(void){
	/* Enable global interrupt bit for the timer */
	SREG |= (1<<7);

	/* Initialize the LCD driver */
	LCD_init();
	LCD_displayString("Welcome");
	_delay_ms(1000);

	/* Initialize the UART driver with:
	 * 8 bit data mode
	 * One stop bit
	 * No parity bit
	 * Baud-rate = 9600 bits/sec
	*/
	UART_Config s_config={EIGHT_BITS,DISABLED,ONE,9600};
	UART_init(&s_config);

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

	/* Wait until MC2 is ready*/
	UART_sendByte(MC1_READY);
	while(UART_recieveByte() != MC2_READY){}






	while(1){
		g_order=UART_recieveByte();
		/* must clear the g_recievedValue after every
		 * switch case executed so it will not execute again */

		switch(g_order){

		case getNewPassword:
			g_order=0;

			getUserNewPassword();
			/*Tell the other MC2 that password is ready */
			UART_sendByte(HMI_PasswordReady);

			sendUserNewPassword();

			break;


		case PasswordMatch :
			g_order=0;
			mainOptions();
			break;


		case passwordsUnmatched :
			g_order=0;
			LCD_clearScreen();
			LCD_displayString("Unmatched");
			_delay_ms(1000) ;
			getUserNewPassword();
			/* Tell the other MC2 to open the door */
			UART_sendByte(HMI_PasswordReady);
			sendUserNewPassword();
			break ;


		case RequestedCorrectPassword :
			g_order=0;
			if(g_key== '+')
			{
				/* Tell the other MC2 to open the door*/
				UART_sendByte(openDoor) ;
			}
			else if(g_key=='-')
			{
				getUserNewPassword();
				/* Tell the other MC2 HMI_PasswordReady is ready */
				UART_sendByte(HMI_PasswordReady);
				sendUserNewPassword();
			}
			break;


		case RequestedINCorrectPassword :
			g_order=0;
			g_flag++;
			if(g_flag==3)
			{
				g_flag=0;
				g_order=errorScreen;
			}
			else
			{
				LCD_clearScreen();
				LCD_displayString("Wrong Password !");
				LCD_displayStringRowColumn(1,0,"Try again !");

				_delay_ms(1000);

				requestPassword();
				/* Tell the other MC2 HMI_Password Ready */
				UART_sendByte(HMI_RequestedPasswordReady);
				sendRequestedPassword();
			}
			break;


		case errorScreen :
			g_order=0;
			LCD_clearScreen();
			LCD_displayString("ERROR!!");

			g_tick=0;
			while(((g_tick) != (1780)));

			mainOptions();
			break ;


		case DoorOpening :
			g_order=0;
			LCD_clearScreen();
			LCD_displayString("DOOR opening...");
			break ;


		case DoorClosing :
			g_order=0;
			LCD_clearScreen();
			LCD_displayString("DOOR closing...");
			break ;


		case DoorIsOpened :
			g_order=0;
			LCD_clearScreen();
			LCD_displayString("DOOR opened");
			break ;


		case DoorIsClosed :
			g_order=0;
			LCD_clearScreen();
			LCD_displayString("DOOR closed");

			_delay_ms(1000);

			break ;


		case RequestPassword :
			g_order=0;
			requestPassword();
			/* Tell the other MC2 HMI_RequestedPasswordReady */
			UART_sendByte(HMI_RequestedPasswordReady);
			sendRequestedPassword();
			break;


		/* */
		default :
			g_order=0;
			break;
		}
	}
}
