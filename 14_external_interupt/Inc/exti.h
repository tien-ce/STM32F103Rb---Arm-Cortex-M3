/*
 * exti.h
 *
 *  Created on: Apr 2, 2026
 *      Author: vantien
 */

#ifndef EXTI_H_
#define EXTI_H_

#include "stm32f1xx.h"
#include "core_cm3.h"
#define IOPCEN		(1U << 4)	// IO port C clock enable
#define AFIOEN		(1U << 0)	// Alternate function IO Clock enable
#define PC13_EXEN	(2U << 4)	// PC13 external interupt enable
#define LINE13_IRQ		(1U << 13)
void pc13_exti_init(void);
#endif /* EXTI_H_ */
