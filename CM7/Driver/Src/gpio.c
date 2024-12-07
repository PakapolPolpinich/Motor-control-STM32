/*
 * gpio.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Admin
 */

#include"gpio.h"

/*********************************************************************
 * @fn      		  - GPIO_pinMode
 * @brief             - Configures the mode, speed, pull-up/pull-down, and alternate function of a GPIO pin.
 *
 * @param[in]         -	*pGPIO points to the GPIO peripheral base address form structure GPIO
 * @param[in]         -	pin for GPIO 0-15
 * @param[in]         -	mode configure  INPUT,OUTPUT,ALTERNATE_FUNCTION,ANALOG
 * @param[in]         -	speed configure LOW_SPEED, MEDIUM_SPEED, FAST_SPEED, HIGH_SPEED
 * @param[in]         -	pupd (pullup_pulldown) configure NO_PUPD, PULL_UP, PULL_DOWN 
 * @param[in]         -	AFRLH (alternate function high and low) AF0-AF15
 *
 * @return            -	None
 *
 * @Note              -

 *//////////////////////////////////////////////////////////////////////
void GPIO_pinMode(GPIO_TypeDef *pGPIO,uint8_t pin,uint8_t mode,uint8_t speed,uint8_t pupd,uint8_t AFRLH){
	static uint16_t clock = 0;
	GPIO_TypeDef * gpio_ports[] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE,GPIOF,GPIOG,GPIOH,GPIOI,GPIOJ,GPIOK};
	uint32_t gpio_enable_bits[] = {RCC_GPIOA, RCC_GPIOB, RCC_GPIOC, RCC_GPIOD, RCC_GPIOE, RCC_GPIOF,RCC_GPIOG,RCC_GPIOH,RCC_GPIOI,RCC_GPIOJ,RCC_GPIOK};

	for (uint8_t i = 0; i <= 10; i++) {
	     if (pGPIO == gpio_ports[i] && !(clock & gpio_enable_bits[i])) {
	          RCC->AHB4ENR |= gpio_enable_bits[i];
	          clock |= gpio_enable_bits[i];
	          break;
	     	 }
	     }
	pGPIO->MODER	&= 	~(0x3 << (pin*2));
	pGPIO->MODER 	|= 	(mode << (pin*2));

	pGPIO->OSPEEDR 	&= 	~(0x3 << (pin*2));
	pGPIO->OSPEEDR 	|= 	(speed << (pin*2));
	pGPIO->PUPDR 	&= 	~(0x3 << (pin*2));
	pGPIO->PUPDR 	|= 	(pupd << (pin*2));

	if(mode == 0x2){
		pGPIO->AFR[pin/8] &= ~(0xF << ((pin%8)*4));
		pGPIO->AFR[pin/8] |= (AFRLH << ((pin%8)*4));
	}

}
