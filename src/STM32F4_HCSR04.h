/*
 * STM32F4_HCSR04.h
 *
 *  Created on: 29/ott/2014
 *      Author: Mirko
 */

#ifndef STM32F4_HCSR04_H_
#define STM32F4_HCSR04_H_

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"


#define SYSCLK						72000000

#define HCSR04_GPIO					GPIOA
#define HCSR04_RCC_GPIO				RCC_APB2Periph_GPIOA
#define HCSR04_Trigger_Pin			GPIO_Pin_6
#define HCSR04_Echo_Pin				GPIO_Pin_4

#define HCSR04_Delay_us_Time		100

void STM32F4_HCSR04_Init();
int STM32F4_HCSR04_getDistance();

void STM32F4_HCSR04_Delay_us(unsigned long nTime);


#endif /* STM32F4_HCSR04_H_ */
