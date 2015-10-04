/*
 * STM32F4_HCSR04.c
 *
 *  Created on: 29/ott/2014
 *      Author: Mirko
 */

#include "STM32F4_HCSR04.h"
#include <stdio.h>

void STM32F4_HCSR04_Init(){
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef timerInitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStruct.GPIO_Pin = HCSR04_Trigger_Pin;
	GPIO_Init(HCSR04_GPIO, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStruct.GPIO_Pin = HCSR04_Echo_Pin;
	GPIO_Init(HCSR04_GPIO, &GPIO_InitStruct);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	timerInitStructure.TIM_Prescaler = 0;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 0xffffffff;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV4;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &timerInitStructure);
	TIM_Cmd(TIM2, ENABLE);
}


int STM32F4_HCSR04_getDistance(){
	int distance = 0;
	int start_echo = 0;
	int end_echo = 0;

	TIM_SetCounter(TIM2, 0);

	GPIO_SetBits(HCSR04_GPIO, HCSR04_Trigger_Pin);
	STM32F4_HCSR04_Delay_us(HCSR04_Delay_us_Time);
	GPIO_ResetBits(HCSR04_GPIO, HCSR04_Trigger_Pin);

	while(GPIO_ReadInputDataBit(HCSR04_GPIO, HCSR04_Echo_Pin) == RESET){
	}

	start_echo = TIM_GetCounter(TIM2);

	while(GPIO_ReadInputDataBit(HCSR04_GPIO, HCSR04_Echo_Pin) != RESET){
	}

	end_echo = TIM_GetCounter(TIM2);

	//printf("Start: %d\n", start_echo);
	//printf("End: %d\n", end_echo);
	distance = (end_echo - start_echo);

	return distance;
}

void STM32F4_HCSR04_Delay_us(unsigned long n) {
	unsigned long i;

	while (n--)  // delay n us
	{
		i = 25;
		while (i--)
			; // delay 1 us
	}
}
