/*
 * SystemClock.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Admin
 */
#include"SystemClock.h"

void Clk_init(){
	// Enable SMPS (Switch Mode Power Supply)
	PWR->CR3 |= (1 << PWR_CR3_SMPSEN_Pos); // Enable SMPS
	// Set Voltage Scaling to Scale 1 because it high frequency
	PWR->D3CR = (0x3 << PWR_D3CR_VOS_Pos);
	// Enable HSE
	RCC->CR |= (1 << RCC_CR_HSEON_Pos);
	while (!(RCC->CR & (1 << RCC_CR_HSERDY_Pos)));//wait for it to be ready
	// PLL source MUX use HSE and set DIVM1
	RCC->PLLCKSELR = RCC_PLLCKSELR_PLLSRC_HSE | RCC_PLLCKSELR_DIVM1_0;// DIVM1 division 1
	// Configure PLL1 (400 MHz SYSCLK, 61.538 MHz for PLL1Q
	RCC->PLL1DIVR = (100 - 1) << RCC_PLL1DIVR_N1_Pos |  // DIVN1 = 100 ->8*100 = 800 MHz
	                (2 - 1) << RCC_PLL1DIVR_P1_Pos |    // DIVP1 = 2 ->800/2 = 400 MHz
	                (13 - 1) << RCC_PLL1DIVR_Q1_Pos;   // DIVQ1 = 13->800/13 = 61.538
	RCC->PLL1FRACR = 0;  // No fractional part
	// Enable PLL1
	RCC->CR |= (1 << RCC_CR_PLL1ON_Pos);
	while (!(RCC->CR & (1 << RCC_CR_PLL1RDY_Pos)));//wait until PLL lock
	//Configure Flash Latency
	FLASH->ACR &= ~(0xF << FLASH_ACR_LATENCY_Pos);  // Clear existing latency bits
	FLASH->ACR |= FLASH_ACR_LATENCY_2WS;            // Set latency to 2 wait states
	//Configure Domain Prescalers
	RCC->D1CFGR = (0x8 << RCC_D1CFGR_HPRE_Pos) |    // HPRE = /2 -> 200 MHz CPU2,AHB1,2
	              (4 << RCC_D1CFGR_D1PPRE_Pos);     // D1PPRE = /2 -> 100 MHz (
	RCC->D2CFGR = (4 << RCC_D2CFGR_D2PPRE1_Pos) |   // D2PPRE1 = /2 -> 100 MHz
	              (4 << RCC_D2CFGR_D2PPRE2_Pos);    // D2PPRE2 = /2 -> 100 MHz
	RCC->D3CFGR = 4 << 4 ;                          // D3PPRE = /2 -> 100 MHz
	// Select PLL1 as System Clock
	RCC->CFGR &= ~(0x3 << RCC_CFGR_SW_Pos);         // Clear system clock switch bits
	RCC->CFGR |= RCC_CFGR_SW_PLL1;                  // Select PLL1 as SYSCLK
	// Wait until PLL1 is used as the system clock
	while ((RCC->CFGR & (0x3 << RCC_CFGR_SWS_Pos)) != RCC_CFGR_SWS_PLL1);
}
