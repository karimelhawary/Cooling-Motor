/*
 * E2PROM.h
 *
 *  Created on: Aug 29, 2023
 *      Author: hp
 */

#ifndef E2PROM_H_
#define E2PROM_H_

#include "std_types.h"

void EEPROM_WRITE(uint32 addr , uint8 data );
uint8 EEPROM_READ(uint32 addr );

#endif /* E2PROM_H_ */
