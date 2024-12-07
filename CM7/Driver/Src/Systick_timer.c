/*
 * Systick_timer.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Admin
 */


#include"Systick_timer.h"

volatile uint32_t millis_counter = 0;

void SysTick_Handler(void){
	millis_counter++;
}

/*********************************************************************
 * @fn      		  - Systick_init
 * @brief             - initial sequence systick counter
 *
 * @param[in]         -	f_cpu CPU clock frequency (Hz)
 * @param[in]         -	Hz interrupt frequency for systick timer it mean interrupt every Hz or 1/Hz
 *
 * @return            -	None
 *
 * @Note              -

 *//////////////////////////////////////////////////////////////////////
void Systick_init(const uint32_t f_cpu, const uint32_t Hz){
	/*calculate of reload value*/
	SysTick->LOAD  = (f_cpu / Hz) - 1; // Ex. 1s/0.0625us -> 16Mhz/1hz (every 1 sec go to interrupt)
									   // Ex. 1ms/0.0625us -> 16Mhz/1000hz tick (every 1ms go to interrupt)
	/*clear current value*/
	SysTick->VAL   =  0;
	/*program control and status register*/
	SysTick->CTRL |= CLKSOURCE | TICKINT ;
	SysTick->CTRL |= COUNTER_ENABLE ;
}

/*********************************************************************
 * @fn      		  - millis
 * @brief             - counter when start Returns the current value of the millis counter
 *
 * @param[in]         -	none
*
 * @return            - current value of millis_counter
 *
 * @Note              - This function provides the elapsed time in milliseconds

 *//////////////////////////////////////////////////////////////////////
uint32_t millis(){
	return millis_counter;
}

/*********************************************************************
 * @fn      		  - delay_ms
 * @brief             - delay or stop  excecution for a specified millisseconds
 *
 * @param[in]         -	ms number of milliseconds to delay
 *
 * @return            - none
 *
 * @Note              -

 *//////////////////////////////////////////////////////////////////////
void delay_ms(uint32_t ms){
	if(ms == 0) return;
	static uint32_t  start;
	start = millis();
		while((millis()) - start < ms);
}
