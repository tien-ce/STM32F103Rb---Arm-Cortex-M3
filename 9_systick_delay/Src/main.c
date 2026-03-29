#include "string.h"
#include "uart.h"
#include  "systick.h"
#include "gpio.h"
#define LED_PIN	5
int main (void) {
	led_init(LED_PIN);
	uart2_rx_tx_init();
	while (1){
		led_toggle(LED_PIN);
		systickDelayMs(1000);
	}
}

