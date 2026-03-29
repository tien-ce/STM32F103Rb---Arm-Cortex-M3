/*
 * systick.h
 *
 *  Created on: Mar 29, 2026
 *      Author: vantien
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "stm32f1xx.h"
#define SYS_CTRL_EN		(1U << 0)
#define SYS_CTRL_INS	(1U << 2)
#define SYS_CTRL_FLAG	(1U << 16)

#define SYSTICK_LOAD_VALUE		8000
void systickDelayMs(int n);
#endif /* SYSTICK_H_ */
