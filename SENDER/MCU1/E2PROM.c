/*
 * E2PROM.c
 *
 *  Created on: Aug 29, 2023
 *      Author: hp
 */
#include "avr/io.h"
#include "E2PROM.h"

void EEPROM_WRITE(uint32 addr , uint8 data )
{
	/* wait for complete write */
	while (EECR & (1<<EEWE));

	/* set up address and data registers*/
	EEAR = addr;
	EEDR = data ;
	/* write 1 to EEMWE*/
	EECR |=(1<< EEMWE);
	/*start EEPROM write */
	EECR |= (1<<EEWE);

}


uint8 EEPROM_READ(uint32 addr )
{
	/* wait for complete write */
		while (EECR & (1<<EEWE));

		/* set up address*/
		EEAR = addr;

		/*start EEPROM read */
		EECR |= (1<<EERE);

		/*return data */
		return EEDR;

}
