#include "string.h"
#include "uart.h"
#include  "systick.h"
#include "gpio.h"
#include "timer.h"
#define LED_PIN	5
int main (void) {
	timer2_pa1_output_compare();
	led_init(LED_PIN);
	while (1){
		if (GPIOA->IDR & (1U << 1)) {
		        GPIOA->ODR |= (1U << LED_PIN);
		}
		else {
		        GPIOA->ODR &= ~(1U << LED_PIN);
		}
	}
}

