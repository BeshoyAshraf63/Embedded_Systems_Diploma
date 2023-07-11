/*
 ============================================================================
 Name        : Beshoy_Ashraf_Mini_Project3.c
 Author      : Beshoy Ashraf
 Description : Mini project3-Embedded Diploma 57
 Date        : 10/12/2021
 ============================================================================
 */

#include "lm35.h"
#include "lcd.h"
#include "dcmotor.h"
#include "adc.h"

int main(void){
	uint8 Temp;
	LCD_init();
	LCD_displayStringRowColumn(0,4,"FAN is OFF");
	LCD_displayStringRowColumn(1,4,"Temp =    C");
	adc_config s_config= {INTERNAL_SEL,ADLAR_RIGHT,ADC_ENABLED,POOLING_MODE,AUTO_TRIGGER_DISABLED,FCPU_8};
	ADC_init(&s_config);
	DcMotor_init();
	DcMotor_Rotate(CLOCK_WISE,0);
	while(1){
		Temp=LM35_getTemeprature();

		if(Temp<30)
		{
			LCD_displayStringRowColumn(0,11,"OFF");
			DcMotor_setSpeed(0);
			LCD_moveCursor(1,11);
			if(Temp >= 10)
			{
				LCD_intgerToString(Temp);
			}
			else
			{
				LCD_intgerToString(Temp);
				/* In case the digital value is  one digit print space in the next digit place */
				LCD_displayCharacter(' ');
			}
		}


		else if( (Temp>=30) && (Temp<60) )
		{
			LCD_displayStringRowColumn(0,11,"ON ");
			DcMotor_setSpeed(25);
			LCD_moveCursor(1,11);
			LCD_intgerToString(Temp);
		}


		else if( (Temp>=60) && (Temp<90) )
		{
			LCD_displayStringRowColumn(0,11,"ON ");
			DcMotor_setSpeed(50);
			LCD_moveCursor(1,11);
			LCD_intgerToString(Temp);
		}


		else if( (Temp>=90) && (Temp<120) )
		{
			LCD_displayStringRowColumn(0,11,"ON ");
			DcMotor_setSpeed(75);
			LCD_moveCursor(1,11);
			if(Temp >= 100)
			{
				LCD_intgerToString(Temp);
			}
			else
			{
				LCD_intgerToString(Temp);
				/* In case the digital value is two or one digits print space in the next digit place */
				LCD_displayCharacter(' ');
			}
		}


		else if(Temp>=120)
		{
			LCD_displayStringRowColumn(0,11,"ON ");
			DcMotor_setSpeed(100);
			LCD_moveCursor(1,11);
			if(Temp >= 100)
			{
				LCD_intgerToString(Temp);
			}
			else
			{
				LCD_intgerToString(Temp);
				/* In case the digital value is two or one digits print space in the next digit place */
				LCD_displayCharacter(' ');
			}
		}
	}
}
