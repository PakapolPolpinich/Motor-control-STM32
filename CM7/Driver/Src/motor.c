/*
 * motor.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Admin
 */

#include"motor.h"

struct motor_pin {
	volatile uint32_t* ln1;
	volatile uint32_t* ln2;
};

struct motor_pin motorPin[] = {
		{&(TIM3->CCR1),&(TIM3->CCR2)},
		{&(TIM3->CCR3),&(TIM3->CCR4)}
};

void motor_init(){
	Pwm_init();
}

/*********************************************************************
 * @fn      		  - rotateMotor
 * @brief             - set speed for motor left and right
 *
 * @param[in]         -	channel 0-1 motor left and right
 * @param[in]         -	speed motor left and right
 * 
 * @return            -	None
 *
 * @Note              -

 *//////////////////////////////////////////////////////////////////////
void rotateMotor(uint8_t channel, int32_t speed){
	if (speed > 0) {
	        *(motorPin[channel].ln1) = (uint32_t)speed; // Forward
	        *(motorPin[channel].ln2) = 0;
	    } else if (speed < 0) {
	        *(motorPin[channel].ln1) = 0;
	        *(motorPin[channel].ln2) = (uint32_t)abs(speed); // Reverse
	    } else {
	        *(motorPin[channel].ln1) = 0; // Stop
	        *(motorPin[channel].ln2) = 0;
	    }
}




