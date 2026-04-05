/*
 * timer.h
 *
 *  Created on: Mar 29, 2026
 *      Author: vantien
 */

#ifndef TIMER_H_
#define TIMER_H_
#include "stm32f1xx.h"
#define TIMER2_CLOCK_EN	(1U << 0)
#define TIMx_OCM2_TOGGLE	(3U << 12)	// Output compare with toggle in channel 2
#define TIMx_CC2_EN		(1U << 4)	// Capture (input)/ Compare (output) enable in channel 2
#define TIMx_CR1_CEN	(1U << 0)	// timer counter enable
#define GPIOA_EN  (1U << 2)	// 0b 0000 0000 0000 0100
#define TIMx_RS_UIF	(1U << 0) 	// Update interrupt flag
void timer2_1hz_init(void);
void timer2_pa1_output_compare(void);
#endif /* TIMER_H_ */
