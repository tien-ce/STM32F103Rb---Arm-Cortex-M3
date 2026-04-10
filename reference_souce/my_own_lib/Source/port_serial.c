/*
 * port_serial.c
 *
 * Created on: Apr 9, 2026
 * Author: Văn Tiến <tien11102004@gmail.com>
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
#include "uart.h"
#define UNUSED(x) (void)(x)

#define eMBPtoeNP(__eMBParity__)				(	((__eMBParity__) == MB_PAR_NONE) ? PAR_NONE :\
													((__eMBParity__) == MB_PAR_ODD) ? PAR_ODD :\
													PAR_EVEN	)

BOOL xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity embparity, UCHAR ucStopBits)
{
	UNUSED(ucPORT);
	eParity eparity = eMBPtoeNP(embparity);
	uart2_init(ulBaudRate, ucDataBits, eparity,ucStopBits);
	uart2_rx_tx_init();
	uart2_enable(FALSE, FALSE);
	return TRUE;
}

void vMBPortSerialEnable(BOOL rxEnable, BOOL txEnable)
{
	uart2_enable(rxEnable, txEnable);
}

BOOL xMBPortSerialPutByte(CHAR byte)
{
	uart2_write(byte);
	return TRUE;
}

BOOL xMBPortSerialGetByte(CHAR *byte)
{
	*byte = uart2_read();
	return TRUE;
}

void USART2_IRQHandler()
{
	/* Checking where does the interrupt come from
	 * Including check status register to check and checking whether that interupt is enable in control1 register
	 * */
	if((USART2->SR & USART_TXE) && (USART2->CR1 & UART_IT_TXE))
	{
		xMBRTUTransmitFSM();
	}
	else if ((USART2->SR & USART_RXNE) && (USART2->CR1 & UART_IT_RXNE))
	{
		xMBRTUReceiveFSM();
	}

}
