// where is the LED connected
// PORT , PIN: Port A, Pin 5
#include "gpio.h"
#define LED_PIN 5
int main (void){
	led_init(LED_PIN);
	while (1){
		led_on(LED_PIN);
		for (int i = 0; i < 100000; i++){}
		led_off(LED_PIN);
		for (int i = 0; i < 100000; i++){}
	}
}
