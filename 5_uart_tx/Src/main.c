#include "stm32f1xx.h"
#include "string.h"
#define USART2_CLK_EN  	(1U << 17)	// Enable clock
#define USART_TX_EN		(1U << 3)
#define USART_EN		(1U << 13)	// Enable USARST prescalers and UASART outputs
#define GPIOA_EN  		(1U << 2)
#define USART_TXE		(1U << 7)

#define SYS_FREQ 		8000000 // (8Mhz in default)
#define APB1_CLK			SYS_FREQ
#define UART_BAUDRATE	115200

static void uart_set_baudrate (USART_TypeDef *USARTx, uint32_t PeriClk, uint32_t baudrate);
void uart2_tx_init (void);
static uint32_t compute_usart_baudrate (uint32_t PeriClk, uint32_t baudrate);
static void uart_write (char c);

int main (void) {
	uart2_tx_init();
	while (1){
		char *buffer = "Hello world";
		int length = strlen(buffer);
		for (char *i = buffer, *end = buffer + length; i != end; i++){
			uart_write(*i);
		}
		uart_write('\n');
		uart_write('\r');
		for (int i = 0; i < 1000000; i++){}
	}
}

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

static void uart_write (char c){
	/*Make sure transmit data register is empty*/
	while (!(USART2->SR && USART_TXE)){}
	/*Write to transmit data register*/
	USART2->DR = c;

}

static void uart_set_baudrate (USART_TypeDef *USARTx, uint32_t PeriClk, uint32_t baudrate)
{
	USARTx->BRR = compute_usart_baudrate (PeriClk, baudrate);
}
static uint32_t compute_usart_baudrate (uint32_t PeriClk, uint32_t baudrate)
{
	return (PeriClk + (baudrate / 2U)) / baudrate;
}
