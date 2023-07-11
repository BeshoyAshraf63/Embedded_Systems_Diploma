/*
 ============================================================================
 Name        : App.c
 Author      : Beshoy Ashraf
 Description : Mini project4-Embedded Diploma 57
 Date        : 10/17/2021
 ============================================================================
 */

#include "ultrasonic.h"
#include "lcd.h"


int main(void){
	uint16 value;
	LCD_init();
	Ultrasonic_init();
	LCD_displayString("Distance=    cm");

	while(1){
		value=Ultrasonic_readDistance();
		if (value>=100)
		{
			LCD_moveCursor(0,10);
			LCD_intgerToString(value);
		}
		else if(value<100)
		{
			LCD_moveCursor(0,10);
			LCD_intgerToString(value);
			LCD_displayCharacter(' ');
		}
	}
}
