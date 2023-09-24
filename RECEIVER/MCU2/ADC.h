/*
 * ADC.h
 *
 *  Created on: Jun 20, 2023
 *      Author: hp
 */

#ifndef ADC_H_
#define ADC_H_

typedef  float  ADC_ReferenceVolatge;
typedef  unsigned int   ADC_Prescaler;

typedef struct{
ADC_ReferenceVolatge ref_volt;
ADC_Prescaler prescaler;
}ADC_ConfigType;

void ADC_init(ADC_ConfigType *Config_Ptr);

int read_ADC(int channel);

#endif /* ADC_H_ */
