/*
 * motor.c
 *
 *  Created on: Jun 20, 2023
 *      Author: hp
 */

#include "common_macros.h" /* For GET_BIT Macro */
#include "gpio.h"
#include "motor.h"

void DcMotor_init(void)
{
	GPIO_setupPortDirection(Dc_Motor1_Port,PORT_OUTPUT);

	GPIO_setupPinDirection(Dc_Motor1_Port,Dc_Motor1_Pin0,PIN_OUTPUT);
	GPIO_setupPinDirection(Dc_Motor1_Port,Dc_Motor1_Pin1,PIN_OUTPUT);
	GPIO_setupPinDirection(Dc_Motor1_Port,Dc_Motor1_E_PIN_ID,PIN_OUTPUT);

	GPIO_setupPortDirection(Dc_Motor2_Port,PORT_OUTPUT);

	GPIO_setupPinDirection(Dc_Motor2_Port,Dc_Motor2_Pin5,PIN_OUTPUT);
	GPIO_setupPinDirection(Dc_Motor2_Port,Dc_Motor2_Pin6,PIN_OUTPUT);
	GPIO_setupPinDirection(Dc_Motor2_Port,Dc_Motor2_E_PIN_ID,PIN_OUTPUT);
}

void DcMotor_RotateAntiClockWise()
{
	GPIO_writePin(Dc_Motor1_Port,Dc_Motor1_Pin0,LOGIC_LOW);
	GPIO_writePin(Dc_Motor1_Port,Dc_Motor1_Pin1,LOGIC_HIGH);

	GPIO_writePin(Dc_Motor2_Port,Dc_Motor2_Pin5,LOGIC_LOW);
	GPIO_writePin(Dc_Motor2_Port,Dc_Motor2_Pin6,LOGIC_HIGH);

}


void DcMotor_RotateClockWise()
{
	GPIO_writePin(Dc_Motor1_Port,Dc_Motor1_Pin0,LOGIC_HIGH);
	GPIO_writePin(Dc_Motor1_Port,Dc_Motor1_Pin1,LOGIC_LOW);

	GPIO_writePin(Dc_Motor2_Port,Dc_Motor2_Pin5,LOGIC_HIGH);
	GPIO_writePin(Dc_Motor2_Port,Dc_Motor2_Pin6,LOGIC_LOW);


}


void DcMotor_TurnOff(void)
{
	GPIO_writePin(Dc_Motor1_Port,Dc_Motor1_Pin0,LOGIC_LOW);
	GPIO_writePin(Dc_Motor1_Port,Dc_Motor1_Pin1,LOGIC_LOW);
	GPIO_writePin(Dc_Motor1_Port,Dc_Motor1_E_PIN_ID,LOGIC_LOW);

	GPIO_writePin(Dc_Motor2_Port,Dc_Motor2_Pin5,LOGIC_LOW);
	GPIO_writePin(Dc_Motor2_Port,Dc_Motor2_Pin6,LOGIC_LOW);
	GPIO_writePin(Dc_Motor1_Port,Dc_Motor2_E_PIN_ID,LOGIC_LOW);
}





