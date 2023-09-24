/*
 * motor.h
 *
 *  Created on: Jun 20, 2023
 *      Author: hp
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#define TOP 255
#define Dc_Motor1_Port	         PORTA_ID
#define Dc_Motor1_Pin0           PIN4_ID
#define Dc_Motor1_Pin1           PIN3_ID
#define Dc_Motor1_E_PIN_ID       PIN2_ID

#define Dc_Motor2_Port	         PORTC_ID
#define Dc_Motor2_Pin5           PIN5_ID
#define Dc_Motor2_Pin6           PIN6_ID
#define Dc_Motor2_E_PIN_ID       PIN7_ID


void DcMotor_init(void);

void DcMotor_RotateClockWise();

void DcMotor_RotateAntiClocKWise();

void DcMotor_TurnOff(void);




#endif /* MOTOR_H_ */
