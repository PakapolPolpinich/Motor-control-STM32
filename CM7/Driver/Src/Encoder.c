/*
 * Encoder.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Admin
 */


#include"Encoder.h"
#include"gpio.h"

void Encoder_init(void){

	GPIO_pinMode(GPIOE,9,ALTERNATE_FUNCTION,LOW_SPEED,NO_PUPD,TIM1_CH1);
	GPIO_pinMode(GPIOE,11,ALTERNATE_FUNCTION,LOW_SPEED,NO_PUPD,TIM1_CH2);
	GPIO_pinMode(GPIOA,0,ALTERNATE_FUNCTION,LOW_SPEED,NO_PUPD,TIM2_CH1);
	GPIO_pinMode(GPIOB,3,ALTERNATE_FUNCTION,LOW_SPEED,NO_PUPD,TIM2_CH2);

	RCC->APB1LENR |= RCC_APB1LENR_TIM2EN;
	RCC->APB2ENR  |= RCC_APB2ENR_TIM1EN;


	TIM1->CCMR1 |= TIM_CCMR1_CC1S_0|TIM_CCMR1_CC2S_0;// input capture mode
	TIM2->CCMR1 |= TIM_CCMR1_CC1S_0|TIM_CCMR1_CC2S_0;
	

	TIM1->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P); // Non-inverted signals signal read for timer  = signal for encoder
	TIM2->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P); // Non-inverted signals
	

	TIM1->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;//set x4 encoder
	TIM2->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;
	
//	TIM2->CR1 &= ~(TIM_CR1_DIR);// count up

	// Ensure non-inverted configuration for complementary signals
	TIM1->CR1 |= TIM_CR1_CEN;
	TIM2->CR1 |= TIM_CR1_CEN;
	
	//create for loop

}

/*********************************************************************
 * @fn      		  - GetValueEncoder
 * @brief             - receive value for encoder  
 *
 * @param[in]         -	channel receive value for encoder TIM1 or TIM2
 * 
 * 
 * @return            -	None
 *
 * @Note              -

 *//////////////////////////////////////////////////////////////////////

int32_t GetValueEncoder(uint8_t channel){
	switch (channel) {
		        case 1: return (int32_t)(TIM1->CNT); break;
		        case 2: return (int32_t)(TIM2->CNT); break;
		    }
}
