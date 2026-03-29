#include "stm32f1xx.h"

#define GPIOA_EN  	(1U << 2)
#define LED_PIN		5
int main (void) {
	RCC->APB2ENR |= GPIOA_EN;
	GPIOA->CRL &= ~(0xFU <<  (LED_PIN * 4)); 	// 0000 -> 24-20
	GPIOA->CRL |= (0x1U << (LED_PIN * 4));	// 0001 -> 24-20
	while (1){
		GPIOA->ODR ^= (1 << LED_PIN);
		for(int i = 0; i < 100000; i++){}
	}
}
