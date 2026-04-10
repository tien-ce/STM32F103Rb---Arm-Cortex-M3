/*
 * systick.c
 *
 *  Created on: Mar 29, 2026
 *      Author: vantien
 */

#include "systick.h"
static uint32_t counter = 0;
static int delayMs = 0;
void systickDelayMs (int n)
{
	/*Configure SYSTICK*/
	// Using number of clock per mili second
	SysTick->LOAD = (SYSTICK_LOAD_VALUE);

	/*Clear systick current value register*/
	SysTick->VAL = 0;

	/*Enable systick and select internal clock source*/
	SysTick->CTRL =	SYS_CTRL_EN;
	SysTick->CTRL |= SYS_CTRL_INS;

	for (int i = 0; i < n; i++){
		/*Wait until COUNTFLAGS IS SET*/
		while (!(SysTick->CTRL & SYS_CTRL_FLAG)){/*Each of this delay 1 mili second*/}
	}
	SysTick->CTRL = 0;
}

void systickinitMs (int n)
{
	/* Set the upper bound value for trigger */
	delayMs = n;
	/*Configure SYSTICK*/
	// Using number of clock per mili second
	SysTick->LOAD = (SYSTICK_LOAD_VALUE);
	/*Clear systick current value register*/
	SysTick->VAL = 0;
	/*Enable systick and select internal clock source*/
	SysTick->CTRL =	SYS_CTRL_EN;
	SysTick->CTRL |= SYS_CTRL_INS;
}

void systickPoll()
{
	if (SysTick->CTRL & SYS_CTRL_FLAG)
		counter ++;
}

bool isSystickExpired()
{
	return (counter >= delayMs);
}

void systickReset()
{
	SysTick->VAL = 0;
	counter = 0;
}



