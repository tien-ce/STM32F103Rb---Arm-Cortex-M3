/*
 * gpio.c
 *
 *  Created on: Mar 28, 2026
 *      Author: vantien
 */
#include "gpio.h"
#include <stdbool.h>
void led_init (int led_pin){
	bool is_low_pin = (led_pin > 7) ? false : true;
	// 1. Enable GPIOA clock
	RCC->APB2ENR |= GPIOA_EN;
	// 2. Set LED PIN to output
	__IO uint32_t	*led_pin_register = is_low_pin 	? &(GPIOA->CRL)
													: &(GPIOA->CRH);
	uint32_t led_pin_offset = is_low_pin ? (led_pin * 4) : ((led_pin - 8) * 4); // 4 bit configuration per pin
	// 2.1 Clear old configuration
	*(led_pin_register) &= ~(0xFU << led_pin_offset);
	// 2.2 Set output mode with 10Mhz 0x1 (CNF=00, MODE=01)
	*(led_pin_register) |= (0x1U << led_pin_offset);
}

void led_on (int led_pin) {
	// Write value 1 into output data register at led_pin offset

	GPIOA->ODR |= (1 << led_pin);
}

void led_off (int led_pin){
	// Write value 0 into output data register at led_pin offset
	GPIOA->ODR |= ~(1 << led_pin);
}

void led_toggle (int led_pin){
	GPIOA->ODR ^= (1 << led_pin);
}
