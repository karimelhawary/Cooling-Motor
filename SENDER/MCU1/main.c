

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
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

/* watchdog timer initization*/
void WDT_INIT(){
    cli();
	wdt_reset();
	wdt_enable(WDTO_30MS); // rest after 30ms
}

int main()
{
    int check =0;
	float Temp_sensor;
	const ADC_ConfigType Conv;
	float Temp_celsius;

	ADC_init(&Conv);
	DcMotor_init();
	UART_init(MYUBRR);

	GPIO_setupPinDirection(PORTB_ID, PIN3_ID,PIN_OUTPUT );
	GPIO_setupPinDirection(PORTA_ID, PIN7_ID,PIN_INPUT );


	//sei(); // global interrupt call
	TIMSK =(1<<TOIE0);  // overflow Interrupt Enable timer0
	TCCR0 = (1<<CS01)|(1<<CS00); // setting the prescaler-64

	/* setting fast pwm timer1 enable */
	TCCR1A = (1<<WGM10) | (1<<WGM12) | (1<<COM1A1) | (1<<COM1B1);
	TCCR1B = (1<<CS10)|(1<<CS11);

	GPIO_setupPinDirection(PORTD_ID,PIN5_ID ,PIN_OUTPUT);


	GPIO_writePin(PORTD_ID,PIN7_ID,LOGIC_LOW);

	while(1)
	{

		Temp_sensor = read_ADC(0);     //channel zero
		Temp_celsius = get_temp(Temp_sensor);
		UART_sendByte(Temp_celsius); // send data to mc2

	   if (Temp_celsius < 20)
	    {
		  // wdt_reset(); // to reset watchdog
		   OV=0;

		   GPIO_writePin(PORTC_ID,PIN7_ID,LOGIC_LOW);
		   DcMotor_TurnOff();

	    }
		else if ( Temp_celsius <= 40 && Temp_celsius >= 20)
		{
			//wdt_reset();

	        OV=0;
			//OCR0 = 12.75 * (Temp_celsius-20); /*if you used timer 0 as pwm*/
	        OCR1A = 12.75 * (Temp_celsius-20); /*equation to control motor speed*/
			GPIO_writePin(PORTC_ID,PIN7_ID,LOGIC_LOW);
		    DcMotor_RotateClockWise();
		}
	   else if (Temp_celsius <= 50 && Temp_celsius > 40)
		{
		   //wdt_reset();
		    OV=0;
		   // OCR0 = 255;
		    OCR1A = 255;

		    DcMotor_RotateClockWise();
           /* to check if push buttom is pressed or not*/
		        if( (PINA & (1<<PD7)) )
		    		{
		        	_delay_ms(100);
		    	     check =1;
		    	     UART_sendByte2(check);
		    		}
		        else
		           {
		    	    check =0 ;
		    		UART_sendByte2(check);
		           }

	    }
	   else if (Temp_celsius > 50 )
	  	{

	     	//OCR0 = 255;
		   OCR1A = 255;

	  	    DcMotor_RotateClockWise();
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
		GPIO_writePin(PORTC_ID,PIN7_ID,LOGIC_HIGH);
		WDT_INIT();
	}

}






