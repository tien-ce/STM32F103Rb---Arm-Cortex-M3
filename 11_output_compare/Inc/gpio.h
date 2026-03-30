/*
 * gpio.h
 *
 *  Created on: Mar 28, 2026
 *      Author: vantien
 */
#include "stm32f1xx.h"
#ifndef GPIO_ADDRESS_H_
#define GPIO_ADDRESS_H_
// Value
#define GPIOA_EN  (1U << 2)	// 0b 0000 0000 0000 0100


void led_init (int led_pin);
void led_on (int led_pin);
void led_off (int led_pin);
void led_toggle (int led_pin);
#endif /* GPIO_ADDRESS_H_ */
