 /******************************************************************************
 *
 * Module: Temperature Sensor
 *
 * File Name: lm35_sensor.h
 *
 * Description: source file for the LM35 Temperature Sensor driver
 *
 * Author: Beshoy Asrhaf
 *
 *******************************************************************************/
#include "lm35.h"
#include "adc.h"


/*******************************************************************************
 *                     Functions  Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemeprature(void){
	uint8 Temp;
	uint16 digital;
	if(g_lmsensor==1){
	/* Read ADC channel where the temperature sensor is connected */
		ADC_readChannel_interrupt(LM35_SENSOR_CHANNEL);
	    digital = g_adcResult;
	}
	else if (g_lmsensor==0){
		digital = ADC_readChannel_pooling(LM35_SENSOR_CHANNEL);
	}

	/* Calculate the temperature from the ADC value*/
	Temp = (uint8)(((uint32)digital*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));

	return Temp;
}
