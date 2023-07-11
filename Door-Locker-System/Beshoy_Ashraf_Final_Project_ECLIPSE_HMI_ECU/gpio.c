 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.c
 *
 * Description: Source file for GPIO AVR driver
 *
 * Author: Beshoy Ashraf
 *
 *******************************************************************************/

#include "gpio.h" /* header file of the driver */
#include "common_macros.h" /*to modify pins with simple macros */

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinDirection(uint8 port_num , uint8 pin_num , GPIO_PinDirectionType direction){
	if((port_num>=NUM_OF_PORTS) || (pin_num>=NUM_OF_PINS))
	{

	}
	else
	{
	switch(port_num){

	case PORTA_ID:
		if(direction==PIN_OUTPUT)
		{
			SET_BIT(DIRECTION_REGA,pin_num);
		}
		else
		{
			CLEAR_BIT(DIRECTION_REGA,pin_num);
		}
		break;
	case PORTB_ID:
		if(direction==PIN_OUTPUT)
		{
			SET_BIT(DIRECTION_REGB,pin_num);
		}
		else
		{
			CLEAR_BIT(DIRECTION_REGB,pin_num);
		}
		break;
	case PORTC_ID:
		if(direction==PIN_OUTPUT)
		{
			SET_BIT(DIRECTION_REGC,pin_num);
		}
		else
		{
			CLEAR_BIT(DIRECTION_REGC,pin_num);
		}
		break;
	case PORTD_ID:
		if(direction==PIN_OUTPUT)
		{
			SET_BIT(DIRECTION_REGD,pin_num);
		}
		else
		{
			CLEAR_BIT(DIRECTION_REGD,pin_num);
		}
		break;
	}
	}
}




/*
 * Description :
 * write the required pin 0/1.
 * If the input port number or pin number or value are not correct, The function will not handle the request.
 * If the pinDirection is input this function will enable/disable the internal pull-up resistor of AVR.
 */
void GPIO_writePin(uint8 port_num,uint8 pin_num,uint8 value){
	if((port_num>=NUM_OF_PORTS) || (pin_num>=NUM_OF_PINS) || (value>1))
	{

	}
	else
	{
	switch(port_num){

	case PORTA_ID:
		if(value==LOGIC_HIGH)
		{
			SET_BIT(OUTPUT_REGA,pin_num);
		}
		else
		{
			CLEAR_BIT(OUTPUT_REGA,pin_num);
		}
		break;
	case PORTB_ID:
		if(value==LOGIC_HIGH)
		{
			SET_BIT(OUTPUT_REGB,pin_num);
		}
		else
		{
			CLEAR_BIT(OUTPUT_REGB,pin_num);
		}
		break;
	case PORTC_ID:
		if(value==LOGIC_HIGH)
		{
			SET_BIT(OUTPUT_REGC,pin_num);
		}
		else
		{
			CLEAR_BIT(OUTPUT_REGC,pin_num);
		}
		break;
	case PORTD_ID:
		if(value==LOGIC_HIGH)
		{
			SET_BIT(OUTPUT_REGD,pin_num);
		}
		else
		{
			CLEAR_BIT(OUTPUT_REGD,pin_num);
		}
		break;
	}
	}
}




/*
 * Description :
 * Read the required pin 0/1 and returns it.
 * If the input port number or pin number or value are not correct, The function will not handle the request and returns logical low value.
 */
uint8 GPIO_readPin(uint8 port_num,uint8 pin_num){

	uint8 readValue=LOGIC_LOW;

	if((port_num>=NUM_OF_PORTS) || (pin_num>=NUM_OF_PINS))
	{

	}
	else
	{
	switch(port_num){

	case PORTA_ID:
		if(BIT_IS_SET(INPUT_REGA,pin_num))
		{
			readValue=LOGIC_HIGH;
		}
		else
		{
			readValue=LOGIC_LOW;
		}
		break;
	case PORTB_ID:
		if(BIT_IS_SET(INPUT_REGB,pin_num))
		{
			readValue=LOGIC_HIGH;
		}
		else
		{
			readValue=LOGIC_LOW;
		}
		break;
	case PORTC_ID:
		if(BIT_IS_SET(INPUT_REGC,pin_num))
		{
			readValue=LOGIC_HIGH;
		}
		else
		{
			readValue=LOGIC_LOW;
		}
		break;
	case PORTD_ID:
		if(BIT_IS_SET(INPUT_REGD,pin_num))
		{
			readValue=LOGIC_HIGH;
		}
		else
		{
			readValue=LOGIC_LOW;
		}
		break;
	}
	}
	return readValue;
}




/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 port_num,GPIO_PortDirectionType direction){
	if((port_num>=NUM_OF_PORTS))
	{

	}
	else
	{
	switch(port_num){

	case PORTA_ID:
		DIRECTION_REGA=direction;
		break;
	case PORTB_ID:
		DIRECTION_REGB=direction;
		break;
	case PORTC_ID:
		DIRECTION_REGC=direction;
		break;
	case PORTD_ID:
		DIRECTION_REGD=direction;
		break;
	}
	}
}




/*
 * Description :
 * Write all pins of the required port by a an entered value.
 * If the input port number or value is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num,uint8 value){
	if((port_num>=NUM_OF_PORTS) || (value>255))
	{

	}
	else
	{
	switch(port_num){

	case PORTA_ID:
		OUTPUT_REGA=value;
		break;
	case PORTB_ID:
		OUTPUT_REGB=value;
		break;
	case PORTC_ID:
		OUTPUT_REGC=value;
		break;
	case PORTD_ID:
		OUTPUT_REGD=value;
		break;
	}
	}
}




/*
 * Description :
 * Read  the required port  value.
 * If the input port number is not correct, The function will not handle the request.
 */
uint8 GPIO_readPort(uint8 port_num){
	uint8 readValue=0;
	if((port_num>=NUM_OF_PORTS))
	{

	}
	else
	{
	switch(port_num){

	case PORTA_ID:
		readValue=OUTPUT_REGA;
		break;
	case PORTB_ID:
		readValue=OUTPUT_REGB;
		break;
	case PORTC_ID:
		readValue=OUTPUT_REGC;
		break;
	case PORTD_ID:
		readValue=OUTPUT_REGD;
		break;
	}
	}
	return readValue;
}
