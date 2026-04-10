/*
 * exti.c
 *
 *  Created on: Apr 2, 2026
 *      Author: vantien
 */


#include "exti.h"

void pc13_exti_init(void)
{
	/* Disable Global interrupt */
	__disable_irq();
	/* Enable clock access for GPIOC */
	RCC->APB2ENR |= IOPCEN;
	/* Enable clock access to SYSCONFG (AFIO in F1, alternate function IO clock)*/
	/* This module allow we to connect the interrupt to specific GPIO */
	RCC->APB2ENR |= AFIOEN;
	/* Select falling edge trigger */

	EXTI->FTSR |= (1U << 13); // Falling trigger rselection egister
	/* Unmask EXTI 13 */
	EXTI->IMR |= (1U << 13); // Interupt marked register (1 is unmark)

	/* Enable EXTI line in NVIC */
	NVIC_EnableIRQ(EXTI15_10_IRQn); // /*!< External Line[15:10] Interrupts

	/* Select PORTC for EXTI 13 (EXTICR4) */
	AFIO->EXTICR[3] &= ~(0xFU);
	AFIO->EXTICR[3] |= 	PC13_EXEN;

	/* Set PC13 to input */
	GPIOC->CRH &= ~(0xF);
	GPIOC->CRH &= ~(0xFU <<  ((13 - 8)* 4)); 	// 0000 -> 24-20
	GPIOC->CRH |= (0x8U << ((13 - 8) * 4));	// 1000 -> 24-20 (00 for intput in mode reg, 10 for input pull up in cnfy)
	/* Enable global interrupt */
	__enable_irq();
}
