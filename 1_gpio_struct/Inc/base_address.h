/*
 * base_address.h
 *
 *  Created on: Mar 28, 2026
 *      Author: vantien
 */
#include <stdint.h>

#define __IO	volatile

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


typedef struct {
    __IO uint32_t CRL;      /* Port configuration register low,  Address offset: 0x00 */
    __IO uint32_t CRH;      /* Port configuration register high, Address offset: 0x04 */
    __IO uint32_t IDR;      /* Port input data register,         Address offset: 0x08 */
    __IO uint32_t ODR;      /* Port output data register,        Address offset: 0x0C */
    __IO uint32_t BSRR;     /* Port bit set/reset register,      Address offset: 0x10 */
    __IO uint32_t BRR;      /* Port bit reset register,          Address offset: 0x14 */
    __IO uint32_t LCKR;     /* Port configuration lock register, Address offset: 0x18 */
} GPIO_TypeDef;

typedef struct {
    __IO uint32_t CR;           /* Clock control register,              Address offset: 0x00 */
    __IO uint32_t CFGR;         /* Clock configuration register,        Address offset: 0x04 */
    __IO uint32_t CIR;          /* Clock interrupt register,           Address offset: 0x08 */
    __IO uint32_t APB2RSTR;     /* APB2 peripheral reset register,     Address offset: 0x0C */
    __IO uint32_t APB1RSTR;     /* APB1 peripheral reset register,     Address offset: 0x10 */
    __IO uint32_t AHBENR;       /* AHB peripheral clock enable register, Address offset: 0x14 */
    __IO uint32_t APB2ENR;      /* APB2 peripheral clock enable register,Address offset: 0x18 */
    __IO uint32_t APB1ENR;      /* APB1 peripheral clock enable register,Address offset: 0x1C */
    __IO uint32_t BDCR;         /* Backup domain control register,      Address offset: 0x20 */
    __IO uint32_t CSR;          /* Control/status register,             Address offset: 0x24 */
} RCC_TypeDef;

#define RCC 		((RCC_TypeDef*)RCC_BASE)
#define GPIOA		((GPIO_TypeDef*)GPIOA_BASE)
#endif /* BASE_ADDRESS_H_ */
