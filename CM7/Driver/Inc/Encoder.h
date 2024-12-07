/*
 * Encoder.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Admin
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include"stm32h7xx.h"

void Encoder_init(void);

int32_t GetValueEncoder(uint8_t channel);


#endif /* INC_ENCODER_H_ */
