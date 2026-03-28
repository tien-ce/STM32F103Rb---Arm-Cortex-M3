/*
 * gpio.h
 *
 *  Created on: Mar 28, 2026
 *      Author: vantien
 */
#include "base_address.h"
#ifndef GPIO_ADDRESS_H_
#define GPIO_ADDRESS_H_

// Register
#define GPIOx_CTRL_LOW_OFFSET		0x00UL // Calculate from GPIOx(A,B,C...) base
#define GPIOx_CTRL_HIGH_OFFSET		0x04UL // Calculate from GPIOx(A,B,C...) base
#define GPIOx_OD_OFFSET			0x0CUL // Out put data register offset
#define GPIOA_OD_R					*(volatile unsigned int *) (GPIOA_BASE + GPIOx_OD_OFFSET)

// Value
#define GPIOA_EN  (1U << 2)	// 0b 0000 0000 0000 0100

void led_init (int led_pin);
void led_on (int led_pin);
void led_off (int led_pin);
void led_toggle (int led_pin);
#endif /* GPIO_ADDRESS_H_ */
