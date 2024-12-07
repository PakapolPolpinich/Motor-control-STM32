/*
 * pwm.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Admin
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

#include "stm32h7xx.h"


void Pwm_init();

void PWM_Setdutycycle(uint8_t channel,uint16_t compare_value);


#endif /* INC_PWM_H_ */
