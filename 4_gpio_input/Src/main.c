#include "stm32f1xx.h"

#define GPIOA_EN  	(1U << 2)
#define GPIOC_EN  	(1U << 4)
#define LED_PIN		5
#define BTN_PIN		13
int main (void) {
	/*Enable clock to GPIOA and GPIOC*/
	RCC->APB2ENR |= GPIOA_EN;
	RCC->APB2ENR |= GPIOC_EN;
	GPIOA->CRL &= ~(0xFU <<  (LED_PIN * 4)); 	// 0000 -> 24-20
	GPIOA->CRL |= (0x1U << (LED_PIN * 4));	// 0001 -> 24-20
	
	// Pin 13 using CTRL HIGH register
	GPIOC->CRH &= ~(0xFU <<  ((BTN_PIN - 8)* 4)); 	// 0000 -> 24-20
	GPIOC->CRH |= (0x8U << ((BTN_PIN - 8) * 4));	// 1000 -> 24-20
	while (1){
		/*Check if BTN is pressed*/
		if (GPIOC->IDR & (1 << BTN_PIN)){
			GPIOA->BSRR = (1 << (LED_PIN + 16));
		}
		else {
			GPIOA->BSRR = (1 << LED_PIN);
		}

	}
}
