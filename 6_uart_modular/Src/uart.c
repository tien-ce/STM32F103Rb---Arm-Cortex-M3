/*
 * uart.c
 *
 *  Created on: Mar 29, 2026
 *      Author: vantien
 */

#include "uart.h"

void uart2_tx_init (void){
	/**** Config UART2 GPIO pin ****/
	// Enable clock to GPIOA
	RCC->APB2ENR |= GPIOA_EN;
	// Set PA2 to alternate functions (10-01 :  Alternate function output Push-pull <---> Output mode, max speed 10 MHz.)
	GPIOA->CRL	&= 	~(0xFU << 2 * 4); // Reset config
	GPIOA->CRL  |=	(0x9U << 2 * 4);  // Set Alternate function to pin
	// Set PA2 alternate function type to UART TX (Don't need to do anything (default at alternate mode is USART_TX)

	/**** Config UART2 Module ****/
	// Enable clock to USART2 module
	RCC->APB1ENR |= USART2_CLK_EN;
	// Cofigure UART baudrate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);
	// Configure the tranfer direction
	USART2->CR1 &= ~(0xFFFFFFFFU);	// Clear previous settings of CR1 ( Parity control disabled and 1 Start bit, 8 Data bits, n Stop bit (in CR2 register) in default)
	USART2->CR2 &= ~(0xFFFFFFFFU);	// Clear previous settings of CR2 (	1 stop bit in default)
	USART2->CR1	|= USART_TX_EN;
	// Enable uart module
	USART2->CR1 |= USART_EN;
}

void uart_write (char c){
	/*Make sure transmit data register is empty*/
	while (!(USART2->SR && USART_TXE)){}
	/*Write to transmit data register*/
	USART2->DR = c;

}

void uart_set_baudrate (USART_TypeDef *USARTx, uint32_t PeriClk, uint32_t baudrate)
{
	USARTx->BRR = compute_usart_baudrate (PeriClk, baudrate);
}
uint32_t compute_usart_baudrate (uint32_t PeriClk, uint32_t baudrate)
{
	return (PeriClk + (baudrate / 2U)) / baudrate;
}
