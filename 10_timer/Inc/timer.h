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
#define TIMx_CR1_CEN	(1U << 0)	// timer counter enable
#define TIMx_CR1_UIF	(1U << 0) 	// Update interrupt flag
void timer2_1hz_init(void);

#endif /* TIMER_H_ */
