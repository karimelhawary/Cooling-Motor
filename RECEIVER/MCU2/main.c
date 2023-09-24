

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <string.h>
#include <avr/wdt.h>
#include "gpio.h"
#include "ADC.h"
#include "temp.h"
#include "motor.h"
#include "uart.h"

#define FOSC 1000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

static int OV =0;
/*to print state in eeprom*/
char nor_mode[20] = "NORMAL STATE  ";
char ABnor_mode[20] = "ABNORMAL STATE";

/* watchdog timer initization*/
void WDT_INIT(){
    cli();
	wdt_reset();
	wdt_enable(WDTO_30MS);// rest after 30ms
}

int main ()
{
	GPIO_setupPinDirection(PORTD_ID,PIN5_ID ,PIN_OUTPUT); // servo

	GPIO_setupPinDirection(PORTC_ID,PIN0_ID ,PIN_OUTPUT); //BUZZER
	GPIO_setupPinDirection(PORTC_ID,PIN2_ID ,PIN_OUTPUT); //RED
	GPIO_setupPinDirection(PORTC_ID,PIN3_ID ,PIN_OUTPUT); //YELLOW
	GPIO_setupPinDirection(PORTC_ID,PIN4_ID ,PIN_OUTPUT); //GREEN


	 GPIO_writePin(PORTC_ID,PIN0_ID,LOGIC_LOW);
	 GPIO_writePin(PORTC_ID,PIN2_ID,LOGIC_LOW);
	 GPIO_writePin(PORTC_ID,PIN3_ID,LOGIC_LOW);
	 GPIO_writePin(PORTC_ID,PIN4_ID,LOGIC_LOW);

	DcMotor_init();
	//GPIO_setupPinDirection(PORTA_ID, PIN2_ID,PIN_OUTPUT );
	UART_init(MYUBRR);

	    DDRB=0xFF;  		/* Make port B as output */

		TIMSK = (1<<TOIE0); // enabling the interrupt
		TCCR0 = (1<<CS01)|(1<<CS00); // setting the prescaler-64
		sei();

		TCNT1 = 0;			/* Set timer1 count zero */
		ICR1 = 2499;         /* top to get 50 hz in timer 1 to use servo*/
		TCCR1A = (1<<WGM11)|(1<<COM1A1);
		TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);

      while(1)
       {

    	  int Temp_celsius=UART_recieveByte();

    	  if (Temp_celsius < 20)
    	 	    {

    		      wdt_reset(); // to reset watchdog
                  /* write sentence state in eeprom */
    		      eeprom_write_block(nor_mode,0,strlen(nor_mode));
	 		      OV=0;
	 		      GPIO_writePin(PORTB_ID,PIN7_ID,LOGIC_LOW);

    		      DcMotor_RotateClockWise();

    	 		  GPIO_writePin(PORTC_ID,PIN0_ID,LOGIC_LOW);
    	 		  GPIO_writePin(PORTC_ID,PIN2_ID,LOGIC_LOW);
    	 		  GPIO_writePin(PORTC_ID,PIN3_ID,LOGIC_LOW);
    	 		  GPIO_writePin(PORTC_ID,PIN4_ID,LOGIC_HIGH);



    	 	    }
    	 		else if ( Temp_celsius <= 40 && Temp_celsius >= 20)
    	 		{
    	 			wdt_reset();

    	 			eeprom_write_block(nor_mode,0,strlen(nor_mode));
     	 		    OV=0;
     	 		    GPIO_writePin(PORTB_ID,PIN7_ID,LOGIC_LOW);
    	 			DcMotor_RotateClockWise();

    	 			 GPIO_writePin(PORTC_ID,PIN0_ID,LOGIC_LOW);
    	 			 GPIO_writePin(PORTC_ID,PIN2_ID,LOGIC_LOW);
    	 			 GPIO_writePin(PORTC_ID,PIN3_ID,LOGIC_HIGH);
    	 			 GPIO_writePin(PORTC_ID,PIN4_ID,LOGIC_LOW);



    	 		}
    	 	   else if (Temp_celsius <= 50 && Temp_celsius > 40)
    	 		{
    	 		  wdt_reset();

    	 		  eeprom_write_block(nor_mode,0,strlen(nor_mode));
    	 		  OV=0;
    	 		  GPIO_writePin(PORTB_ID,PIN7_ID,LOGIC_LOW);

    	 		  GPIO_writePin(PORTC_ID,PIN0_ID,LOGIC_LOW);
    	 		  GPIO_writePin(PORTC_ID,PIN2_ID,LOGIC_HIGH);
    	 		  GPIO_writePin(PORTC_ID,PIN3_ID,LOGIC_LOW);
    	 		  GPIO_writePin(PORTC_ID,PIN4_ID,LOGIC_LOW);

    	 		 /* to check if push buttom is pressed or not*/
                    int check_rec = UART_recieveByte2();
    	 		    if (1== check_rec)
    	 		    {
    	 		     	 DcMotor_TurnOff();
    	 		    }
    	 		    else
    	 		    {

    	 		    	DcMotor_RotateClockWise();
                    }

    	 		}
    	 	   else if (Temp_celsius > 50 )
    	 	  	{
      /* to still turn off motor and data in eeprom till 7 sec*/
    	 		       if (OV >= 429)
    	 		       {
    	 		    	  eeprom_write_block(ABnor_mode,0,strlen(ABnor_mode));
    	 			      DcMotor_TurnOff();
    	 		       }
    	 		       else
    	 		       {
    	 		    	  eeprom_write_block(nor_mode,0,strlen(nor_mode));
    	 		          DcMotor_RotateClockWise();
    	 		       }

    	 		  GPIO_writePin(PORTC_ID,PIN0_ID,LOGIC_HIGH);
    	          GPIO_writePin(PORTC_ID,PIN2_ID,LOGIC_HIGH);
    	 		  GPIO_writePin(PORTC_ID,PIN3_ID,LOGIC_LOW);
    	 		  GPIO_writePin(PORTC_ID,PIN4_ID,LOGIC_LOW);

    	 	  	}
        }

}
/*  ISR of interrupt overflow timer0*/
ISR(TIMER0_OVF_vect)
{
	OV++;
	/* make 428 ov to get 7 sec
	 * time_clk = 2^8(bits) * (64(prescaler)/1Mhz(fre.MCU))= 16.3ms
	 * to get 7 sec -->> 7/time_clk = 429 */
	if(OV == 429)
	{
		OCR1A = 65; // to servo with 90 degree
		eeprom_write_block(ABnor_mode,0,strlen(ABnor_mode));
		GPIO_writePin(PORTB_ID,PIN7_ID,LOGIC_HIGH);/* to check enable interrupt*/
		DcMotor_TurnOff();
	}
	else if (OV==735) // after 5sec after enable interrupt
	{
		GPIO_writePin(PORTD_ID,PIN7_ID,LOGIC_HIGH);
		WDT_INIT(); // enable watch dog and reset
	}
}
