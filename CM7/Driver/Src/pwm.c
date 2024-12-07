/*
 * pwm.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Admin
 */

#include"pwm.h"
#include"gpio.h"

void Pwm_init(){
	
	RCC->APB1LENR |= RCC_APB1LENR_TIM3EN;

	GPIO_pinMode(GPIOB,0,ALTERNATE_FUNCTION,LOW_SPEED,NO_PUPD,TIM3_CH3);//ch3
	GPIO_pinMode(GPIOB,1,ALTERNATE_FUNCTION,LOW_SPEED,NO_PUPD,TIM3_CH4);//ch4
	GPIO_pinMode(GPIOB,5,ALTERNATE_FUNCTION,LOW_SPEED,NO_PUPD,TIM3_CH2);//ch2
	GPIO_pinMode(GPIOC,6,ALTERNATE_FUNCTION,LOW_SPEED,NO_PUPD,TIM3_CH1);//ch1

	TIM3->CCMR1 &= ~(TIM_CCMR1_CC1S|TIM_CCMR1_CC2S);//set output compare channel 1 and 2
	TIM3->CCMR2 &= ~(TIM_CCMR2_CC3S|TIM_CCMR2_CC4S);//set output compare channel 3 and 4

	TIM3->CCER &= ~(TIM_CCER_CC1P|TIM_CCER_CC2P|TIM_CCER_CC3P|TIM_CCER_CC4P); // set OC is active high when condition is true

	TIM3->CCMR1 &= ~((0xF << 4)|(0xF<<12));// PWM Mode for Channel 1, 2
	TIM3->CCMR1 |= ((0x6 << 4)|(0x6<<12));
	TIM3->CCMR2 &= ~((0xF << 4)|(0xF<<12));// PWM Mode for Channel 3, 4
	TIM3->CCMR2 |= ((0x6 << 4)|(0x6<<12));


	TIM3->PSC = 1;
	TIM3->ARR = 65536-1; //ARR 16 bit

	TIM3->CCMR1 |= (TIM_CCMR1_OC1PE|TIM_CCMR1_OC2PE);//enable OC
	TIM3->CCMR2 |= (TIM_CCMR2_OC3PE|TIM_CCMR2_OC3PE);

	TIM3->CCER |= (TIM_CCER_CC1E|TIM_CCER_CC2E|TIM_CCER_CC3E|TIM_CCER_CC4E); //enable pwm output
	TIM3->CR1	|= TIM_CR1_CEN;
}


/*********************************************************************
 * @fn      		  - PWM_Setdutycycle
 * @brief             - Send PWM 
 *
 * @param[in]         -	channel set channel pwm 1-4
 * @param[in]         -	compare_value 0-65535 
 * 
 *
 * @return            -	None
 *
 * @Note              -

 *//////////////////////////////////////////////////////////////////////

void PWM_Setdutycycle(uint8_t channel,uint16_t compare_value){
	 switch (channel) {
	        case 1: TIM3->CCR1 = compare_value; break;
	        case 2: TIM3->CCR2 = compare_value; break;
	        case 3: TIM3->CCR3 = compare_value; break;
	        case 4: TIM3->CCR4 = compare_value; break;
	    }
}

