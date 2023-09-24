/*
 * temp.c
 *
 *  Created on: Jun 22, 2023
 *      Author: hp
 */
#include "temp.h"

float get_temp(float AdcTemp)
{
float temp_celsius = 	AdcTemp * 2.5f ;   /* 2560(mv) / 1024(10-bits) => 2.5 */

temp_celsius /= 10.00 ;     // The Sensitivty of LM35 is 10 mV/degree Celsius

return temp_celsius;
}
