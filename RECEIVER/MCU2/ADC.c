/*
 * ADC.c
 *
 *  Created on: Jun 20, 2023
 *      Author: hp
 */
#include "gpio.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "avr/io.h" /* To use the IO Ports Registers */
#include "std_types.h"
#include "ADC.h"

/*const ADC_ConfigType*Config_Ptr*/
void ADC_init(ADC_ConfigType *Config_Ptr){
	/*CHOOSE REFERENCE :
	 * INTERNAL 2.56V WITH EXTERNAL CAP @ AREF PIN
	 * */
	 ADMUX |= (1<<REFS0) | (1<<REFS1);
	 Config_Ptr->ref_volt = ADMUX ;
	 /*CHOOSE PRESCALER :
	  * DIVISION FACTOR = 8
	  * */
	 ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | ~(1<<ADPS2);
	 Config_Ptr->prescaler = ADCSRA;

	ADCSRA |= (1<<ADEN);  //ENABLE ADC

}

int read_ADC(int channel)
{

channel &= 0b00000111; //ch 0 -> 7

ADMUX &= 0xF8 ;
ADMUX |= channel;

/* START CONVERSTION */
ADCSRA |= (1<<ADSC);


/*WAIT TO END CONVERSION
 * RUN THE LOOP TILL ADCS =0
 * */
while(ADCSRA & (1<<ADSC));


return ADCL | (ADCH <<8);


}

