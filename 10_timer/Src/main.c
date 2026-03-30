#include "string.h"
#include "uart.h"
#include  "systick.h"
#include "gpio.h"
#include "timer.h"
#define LED_PIN	5
int main (void) {
	led_init(LED_PIN);
	uart2_rx_tx_init();
	timer2_1hz_init();
	while (1){
		led_toggle(LED_PIN);
		while (!(TIM2->SR & TIMx_CR1_UIF)){}	// Wait for Update Interrupt Flag
		/*Clear flag*/
		TIM2->SR &= ~(TIMx_CR1_UIF);
	}
}

