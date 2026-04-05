#include "string.h"
#include "uart.h"
#include  "systick.h"
#include "gpio.h"
#include "timer.h"
#include "exti.h"
#define LED_PIN	5
int main (void) {
	pc13_exti_init();
	led_init(LED_PIN);
	while (1){

	}
}

void EXTI15_10_IRQHandler(void)
{
	/* We enable lines 10-15 (EXTI15_10) so we should check first */
	if (EXTI->PR & LINE13_IRQ)
	{
		/* Clear PR flag */
		EXTI->PR = LINE13_IRQ;	// Write 1 into pending register
		/* Toggle Led */
		led_toggle(LED_PIN);
	}
}
