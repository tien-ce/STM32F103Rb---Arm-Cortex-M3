/*
 * timer.c
 *
 *  Created on: Mar 29, 2026
 *      Author: vantien
 */

#include "timer.h"

void timer2_1hz_init(void)
{
	/*Enable clock access to timer 2*/
	RCC->APB1ENR |= TIMER2_CLOCK_EN;
	/*Set the prescaler value*/
	TIM2->PSC	=	800 - 1;	// 8Mhz / 800 = 10 000 Hz
	/*Set the auto-load value*/
	TIM2->ARR	=	10000 - 1;	// 1Hz
	/*Clear the counter*/
	TIM2->CNT	=	0;
	/*Enable the timer*/
	TIM2->CR1	|= TIMx_CR1_CEN;
}
