/*
 * base_address.h
 *
 *  Created on: Mar 28, 2026
 *      Author: vantien
 */

#ifndef BASE_ADDRESS_H_
#define BASE_ADDRESS_H_

#define PERIPHERAL_BASE 0x40000000UL
#define APB2_OFFSET 	0x00010000UL
#define AHP_OFFSET 		0x00018000UL

#define APB2_BASE (PERIPHERAL_BASE + APB2_OFFSET)	// 0x4001 0000
#define AHP_BASE  (PERIPHERAL_BASE + AHP_OFFSET)	// 0x4001 8000

#define GPIOA_OFFSET 	0x00000800UL
#define GPIOA_BASE (APB2_BASE + GPIOA_OFFSET)

#define RCC_OFFSET 		0x00009000UL
#define RCC_BASE		(AHP_BASE + RCC_OFFSET)	// 0x4002 1000
#define APB2_EN_OFFSET	0x18UL
#define APB2_EN_R		*(volatile unsigned int*) (RCC_BASE + APB2_EN_OFFSET)

#endif /* BASE_ADDRESS_H_ */
