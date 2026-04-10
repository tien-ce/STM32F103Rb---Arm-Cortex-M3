/*
 * port_timer.c
 *
 *  Created on: Apr 9, 2026
 *      Author: vantien
 *
 * License: MIT
 * Copyright (c) 2026 Văn Tiến
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#include "modbus_rtu/port.h"
#include "modbus_rtu/mbport.h"
#include "modbus_rtu/mbrtu.h"
#include "timer.h"

BOOL xMBPortTimersInit( USHORT usTim1Timerout50us )
{
	timer2_mHz_init(usTim1Timerout50us);
	return true;
}

void vMBPortTimersEnable( void )
{
	timer2_enable();
	timer2_interrupt_enable();
}

void vMBPortTimersDisable( void )
{
	timer2_disable();
}


/**
 * @brief This function handles TIM2 global interrupt.
 */
void TIM2_IRQHandler( void )
{
	if (__HAL_GPTIM_GET_FLAG(GP_TIM2,TIM_FLAG_UPDATE) && __HAL_GPTIM_GET_IT_SOURCE(GP_TIM2,TIM_IT_UPDATE))
	{
		__HAL_GPTIM_CLEAR_FLAG(GP_TIM2,TIM_FLAG_UPDATE);
		xMBRTUTimerT35Expired();
	}
}
