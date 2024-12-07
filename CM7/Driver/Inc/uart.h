/*
 * uart.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Admin
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include"stm32h7xx.h"
#include"gpio.h"

void USART3_Init(void);
void USART3_SendChar(char ch);
char USART3_ReceiveChar(void);
void USART3_SendString(char* str);
void USART3_DMAInit(volatile uint32_t *memory_buffer,uint32_t buffer_size);

void  USART_TxSenddata(USART_TypeDef* pUSART,uint8_t* word,uint8_t size);


#endif /* INC_UART_H_ */
