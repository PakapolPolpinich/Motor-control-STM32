/*
 * uart.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Admin
 */

#include "uart.h"

void USART3_Init(void)
{
	RCC->AHB4ENR |= RCC_AHB4ENR_GPIODEN;//enable AHB4 GPIOD
    RCC->APB1LENR |= RCC_APB1LENR_USART3EN;//enable APB1 USART3
   
    // Configure GPIOD pins for USART3 TX (PD8) and RX (PD9)
    GPIOD->MODER &= ~((3U << (8 * 2)) | (3U << (9 * 2))); // Clear mode for PD8, PD9
    GPIOD->MODER |= (2U << (8 * 2)) | (2U << (9 * 2));    // Set to alternate function
    GPIOD->AFR[1] |= (7U << ((8 - 8) * 4)) | (7U << ((9 - 8) * 4)); // AF7 for USART3 // AF7 for USART3

    // Configure USART3
    USART3->CR1 &= ~USART_CR1_UE;  // Disable USART3 to configure

    // Set baud rate
    USART3->BRR = 0x364; //set baudrate 100000000/115200

    // Enable transmitter and receiver
    USART3->CR1 |= USART_CR1_TE | USART_CR1_RE;

    // Enable USART3
    USART3->CR1 |= USART_CR1_UE;
}

void USART3_SendChar(char ch)
{
    while (!(USART3->ISR & (1<<7)));// Wait until TXFNF is set
    USART3->TDR = ch & (uint8_t)0xFF;
}

void USART3_SendString(char* str)
{
    while (*str)
    {
        USART3_SendChar(*str++);
    }
    while (!(USART3->ISR & (1<<6)));
}
