/*
 * uart.h
 *
 *  Created on: Mar 29, 2026
 *      Author: vantien
 */
#include "stm32f1xx.h"
#include <stdint.h>
#include <stdbool.h>
#ifndef UART_H_
#define UART_H_
#define USART2_CLK_EN  	(1U << 17)	// Enable clock
#define USART_TX_EN		(1U << 3)
#define USART_RX_EN		(1U << 2)
#define USART_EN		(1U << 13)	// Enable USARST prescalers and UASART outputs
#define GPIOA_EN  		(1U << 2)
#define USART_TXE		(1U << 7)
#define USART_RXNE		(1U << 5)

#define SYS_FREQ 		8000000 // (8Mhz in default)
#define APB1_CLK			SYS_FREQ
#define UART_BAUDRATE	115200

/* Exported constants --------------------------------------------------------*/
/** @defgroup UART_Exported_Constants UART Exported Constants
  * @{
  */

/** @defgroup UART_Error_Code UART Error Code
  * @{
  */
#define HAL_UART_ERROR_NONE              0x00000000U   /*!< No error            */
#define HAL_UART_ERROR_PE                0x00000001U   /*!< Parity error        */
#define HAL_UART_ERROR_NE                0x00000002U   /*!< Noise error         */
#define HAL_UART_ERROR_FE                0x00000004U   /*!< Frame error         */
#define HAL_UART_ERROR_ORE               0x00000008U   /*!< Overrun error       */
#define HAL_UART_ERROR_DMA               0x00000010U   /*!< DMA transfer error  */
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
#define  HAL_UART_ERROR_INVALID_CALLBACK 0x00000020U   /*!< Invalid Callback error  */
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup UART_Word_Length UART Word Length
  * @{
  */
#define UART_WORDLENGTH_8B                  0x00000000U
#define UART_WORDLENGTH_9B                  ((uint32_t)USART_CR1_M)			//(1U << 12): M is bit 12 in CR1
/**
  * @}
  */

/** @defgroup UART_Stop_Bits UART Number of Stop Bits
  * @{
  */
#define UART_STOPBITS_1                     0x00000000U
#define UART_STOPBITS_2                     ((uint32_t)USART_CR2_STOP_1)	// (1U << 13): Bit 13 in CR2
/**
  * @}
  */

/** @defgroup UART_Parity UART Parity
  * @{
  */
#define UART_PARITY_NONE                    0x00000000U
#define UART_PARITY_EVEN                    ((uint32_t)USART_CR1_PCE)
#define UART_PARITY_ODD                     ((uint32_t)(USART_CR1_PCE | USART_CR1_PS))
/**
  * @}
  */

/** @defgroup UART_Hardware_Flow_Control UART Hardware Flow Control
  * @{
  */
#define UART_HWCONTROL_NONE                  0x00000000U
#define UART_HWCONTROL_RTS                   ((uint32_t)USART_CR3_RTSE)
#define UART_HWCONTROL_CTS                   ((uint32_t)USART_CR3_CTSE)
#define UART_HWCONTROL_RTS_CTS               ((uint32_t)(USART_CR3_RTSE | USART_CR3_CTSE))
/**
  * @}
  */

/** @defgroup UART_Mode UART Transfer Mode
  * @{
  */
#define UART_MODE_RX                        ((uint32_t)USART_CR1_RE)
#define UART_MODE_TX                        ((uint32_t)USART_CR1_TE)
#define UART_MODE_TX_RX                     ((uint32_t)(USART_CR1_TE | USART_CR1_RE))
/**
  * @}
  */

/** @defgroup UART_State UART State
  * @{
  */
#define UART_STATE_DISABLE                  0x00000000U
#define UART_STATE_ENABLE                   ((uint32_t)USART_CR1_UE)
/**
  * @}
  */

/* Uart interruptions flag mask */
#define UART_IT_MASK                    0x0000FFFFU
#define UART_CR1_REG_INDEX 				1U
#define UART_CR2_REG_INDEX				2U
#define UART_CR3_REG_INDEX 				3U
/** @defgroup UART_Interrupt_definition  UART Interrupt Definitions
  *        Elements values convention: 0xY000XXXX
  *           - XXXX  : Interrupt mask (16 bits) in the Y register
  *           - Y  : Interrupt source register (2bits)
  *                   - 0001: CR1 register
  *                   - 0010: CR2 register
  *                   - 0011: CR3 register
  * @{
  *
 */
#define UART_IT_TXE						((uint32_t)(UART_CR1_REG_INDEX << 28U | USART_CR1_TXEIE))
#define UART_IT_RXNE                   	((uint32_t)(UART_CR1_REG_INDEX << 28U | USART_CR1_RXNEIE))
/*	See these define in stm32f103xb.h
 * 	#define USART_CR1_TXEIE_Pos                 (7U)
	#define USART_CR1_TXEIE_Msk                 (0x1UL << USART_CR1_TXEIE_Pos)
	#define USART_CR1_TXEIE                     USART_CR1_TXEIE_Msk		(1U << 7)
*/

/**
  * @}
*/

/** @defgroup UART_Interrupt_definition  UART Interrupt Definitions
  *
  * @{
  *
 */

/* @brief Enable uart2 interupt
 * @param __INTERRUPT__ specifies the uart source need to be enable
 * 		This paramater can be one of the following values:
 * 		@arg UART_IT_TXE: 	Transmit data register empty interupt
 * 		@arg UART_IT_RXNE: 	Recive data register not empty interupt
 * @retval None
 * */

#define	UART2_ENABLE_IT(__INTERRUPT__) (((__INTERRUPT__) >> 28) == UART_CR1_REG_INDEX) ? (USART2->CR1	|=	((__INTERRUPT__) & UART_IT_MASK)) :\
										(((__INTERRUPT__) >> 28) == UART_CR2_REG_INDEX) ? (USART2->CR2	|=  ((__INTERRUPT__) & UART_IT_MASK)) :\
																						  (USART2->CR3	|=  ((__INTERRUPT__) & UART_IT_MASK))

/* @brief Enable uart2 interupt
 * @param __INTERRUPT__ specifies the uart source need to be disable
 * 		This paramater can be one of the following values:
 * 		@arg UART_IT_TXE: 	Transmit data register empty interupt
 * 		@arg UART_IT_RXNE: 	Recive data register not empty interupt
 * @retval None
 * */
#define	UART2_DISABLE_IT(__INTERRUPT__) (((__INTERRUPT__) >> 28) == UART_CR1_REG_INDEX) ? (USART2->CR1	&=	~((__INTERRUPT__) & UART_IT_MASK)) :\
										(((__INTERRUPT__) >> 28) == UART_CR2_REG_INDEX) ? (USART2->CR2	&=  ~((__INTERRUPT__) & UART_IT_MASK)) :\
																						  (USART2->CR3	&=  ~((__INTERRUPT__) & UART_IT_MASK))
/**
 * @}
 */



typedef enum
{
	 PAR_NONE, /* None parity */
	 PAR_ODD,  /* Odd parity */
	 PAR_EVEN  /* Even parity */
}eParity;

/* Exported functions */
void uart_set_baudrate (USART_TypeDef *USARTx, uint32_t PeriClk, uint32_t baudrate);
void uart2_rx_tx_init (void);
void uart2_init(unsigned long baudrate, unsigned char databit, eParity parity, unsigned char stopbit);
void uart2_write (char c);
char uart2_read (void);
void uart2_enable (bool rxEn, bool txEn);
uint32_t compute_usart_baudrate (uint32_t PeriClk, uint32_t baudrate);

/* Interupt relation functions */
void uart2_nvic_en();	/* Enable nvic for uart2 */
void uart2_rxne_ie();	/* Rx not empty interrupt enable */
void uart2_txe_ie();		/* Tx empty interrupt enable */
#endif /* UART_H_ */
