/*
 * uart.h
 *
 *  Created on: Mar 29, 2026
 *      Author: vantien
 */
#include "stm32f1xx.h"
#ifndef UART_H_
#define UART_H_
#define USART2_CLK_EN  	(1U << 17)	// Enable clock
#define USART_TX_EN		(1U << 3)
#define USART_EN		(1U << 13)	// Enable USARST prescalers and UASART outputs
#define GPIOA_EN  		(1U << 2)
#define USART_TXE		(1U << 7)

#define SYS_FREQ 		8000000 // (8Mhz in default)
#define APB1_CLK			SYS_FREQ
#define UART_BAUDRATE	115200

void uart_set_baudrate (USART_TypeDef *USARTx, uint32_t PeriClk, uint32_t baudrate);
void uart2_tx_init (void);
uint32_t compute_usart_baudrate (uint32_t PeriClk, uint32_t baudrate);
void uart_write (char c);


#endif /* UART_H_ */
