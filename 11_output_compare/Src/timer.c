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

void timer2_pa1_output_compare(void)
{

	/**** Config output compare pin ****/
	// Enable clock to GPIOA
	RCC->APB2ENR |= GPIOA_EN;
	// Set PA1 to alternate functions (10-01 :  Alternate function output Push-pull <---> Output mode, max speed 10 MHz.)
	GPIOA->CRL	&= 	~(0xFU << (1 * 4)); // Reset config
	GPIOA->CRL  |=	(0x9U << (1 * 4));  // Set Alternate function to pin
	// Set PA1 alternate function type to Timer 2 channel 2 output compare (Don't need to do anything (default at alternate mode is USART_TX)

	/*Enable clock access to timer 2*/
	RCC->APB1ENR |= TIMER2_CLOCK_EN;
	/*Set the prescaler value*/
	TIM2->PSC	=	800 - 1;	// 8Mhz / 800 = 10 000 Hz
	/*Set the auto-load value*/
	TIM2->ARR	=	10000 - 1;	// 1Hz

	/* Set output compare toggle mode in channel 2*/
	TIM2->CCMR1 &= ~(7U << 12);
	TIM2->CCMR1 |= TIMx_OCM2_TOGGLE;
	/* Enable output compare in channel 2 */
	TIM2->CCER	|= TIMx_CC2_EN;

	/*Clear the counter*/
	TIM2->CNT	=	0;
	/*Enable the timer*/
	TIM2->CR1	|= TIMx_CR1_CEN;
}
