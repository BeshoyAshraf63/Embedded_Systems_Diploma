 /******************************************************************************
 *
 * Module: Temperature Sensor
 *
 * File Name: lm35_sensor.h
 *
 * Description: header file for the LM35 Temperature Sensor driver
 *
 * Author: Beshoy Ashraf
 *
 *******************************************************************************/

#ifndef LM35_H_
#define LM35_H_

#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LM35_SENSOR_CHANNEL          ADC2
#define SENSOR_MAX_TEMPERATURE       150
#define SENSOR_MAX_VOLT_VALUE        1.5



/*******************************************************************************
 *                                Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */
uint8 LM35_getTemeprature(void);

#endif /* LM35_H_ */
