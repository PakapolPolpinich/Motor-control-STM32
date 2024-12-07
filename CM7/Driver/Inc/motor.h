/*
 * motor.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Admin
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include"stm32h7xx.h"
#include"pwm.h"
#include <stdlib.h>

void motor_init();
void rotateMotor(uint8_t channal, int32_t speed);
float ChangetoRPM(long Pulse, uint8_t i);


#endif /* INC_MOTOR_H_ */
