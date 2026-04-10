/*
 * uart.c
 *
 *  Created on: Mar 29, 2026
 *      Author: vantien
 */

#include "uart.h"

void uart2_rx_tx_init (void){
	/**** Config UART2 GPIO pin ****/
	// Enable clock to GPIOA
	RCC->APB2ENR |= GPIOA_EN;
	// Enable clock to USART2 module
	RCC->APB1ENR |= USART2_CLK_EN;
	// Set PA2 to alternate functions (10-01 :  Alternate function output Push-pull <---> Output mode, max speed 10 MHz.)
	GPIOA->CRL	&= 	~(0xFU << (2 * 4)); // Reset config
	GPIOA->CRL  |=	(0x9U << (2 * 4));  // Set Alternate function to pin
	// Set PA2 alternate function type to UART TX (Don't need to do anything (default at alternate mode is USART_TX)

	// Set PA3 to alternate functions (10-01 :  Alternate function output Push-pull <---> Output mode, max speed 10 MHz.)
	GPIOA->CRL	&=	~(0xFU << ( 3 * 4));
	GPIOA->CRL  |=	(0x9U << (3 * 4));  // Set Alternate function to pin
	// Set PA3 alternate function type to UART RX (Don't need to do anything (default at alternate mode is USART_TX)

	USART2->CR1 |= USART_TX_EN;			// Enable TX
	USART2->CR1 |= USART_RX_EN;			// Enable RX
}

void uart2_init(unsigned long ulbaudrate, unsigned char ucdatabits, eParity eparity,unsigned char stopbit)
{
	/**** Config UART2 Module ****/
	// Enable clock to USART2 module
	RCC->APB1ENR |= USART2_CLK_EN;
	// Cofigure UART baudrate
	uart_set_baudrate(USART2, APB1_CLK, ulbaudrate);
	// Configure the tranfer direction
	USART2->CR1 &= ~(0xFFFFFFFFU);	// Clear previous settings of CR1 ( Parity control disabled and 1 Start bit, 8 Data bits, n Stop bit (in CR2 register) in default)
	USART2->CR2 &= ~(0xFFFFFFFFU);	// Clear previous settings of CR2 (	1 stop bit in default)
	if (ucdatabits !=8 && ucdatabits !=9){
		ucdatabits = 8;		// Default
	}
	/* Set up data bit length */
	switch (ucdatabits){
		case 8:
			USART2->CR1 &= ~(USART_CR1_M);
			break;
		case 9:
			USART2->CR1 |= (USART_CR1_M);
		default:
			break;
	}
	/* Setup stop bit length */
	USART2->CR2 &= ~(3U << 13); // Clear bit
	switch (stopbit){
		case 1:
			break;
		case 2:
			USART2->CR2 |= UART_STOPBITS_2;
			break;
		default:
			break;
	}
	/* Set up parity */
	switch (eparity)
	{
		case PAR_NONE:
			USART2->CR1 &= ~(1U << 10);	// Parity disable
			break;
		case PAR_EVEN:
			USART2->CR1 |= (1U << 10);
			USART2->CR1 &= ~(1U << 9);	// Selection register (0 for even)
			break;
		case PAR_ODD:
			USART2->CR1 |= (1U << 10);
			USART2->CR1 |= (1U << 9);	// Selection register (1 for odd)
			break;
	}

	// Enable uart module
	USART2->CR1 |= USART_EN;
}

void uart2_enable (bool rxEn, bool txEn)
{
	NVIC_EnableIRQ(USART2_IRQn);
	if (txEn)
		USART2->CR1	|= UART_IT_TXE;
	else
		USART2->CR1	&= ~UART_IT_TXE;
	if (rxEn)
		USART2->CR1 |= UART_IT_RXNE;
	else
		USART2->CR1 &= ~UART_IT_RXNE;
	// Re-enable UART interrupt only if at least one direction is active
	if( rxEn || txEn )
		NVIC_EnableIRQ(USART2_IRQn);
}

char uart2_read (void)
{
	/*Make sure recive data register is not empty*/
	while (!(USART2->SR & USART_RXNE)) {}
	/*Read data from data register*/
	return USART2->DR;
}
void uart2_write (char c){
	/*Make sure transmit data register is empty*/
	while (!(USART2->SR & USART_TXE)){}
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
void uart2_nvic_en()
{
	NVIC_EnableIRQ(USART2_IRQn);
}
void uart2_rxne_ie()
{
	UART2_ENABLE_IT(UART_IT_RXNE);
}
void uart2_txe_ie()
{
	UART2_ENABLE_IT(UART_IT_TXE);
}
