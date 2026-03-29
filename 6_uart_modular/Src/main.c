#include "string.h"
#include "uart.h"

int main (void) {
	uart2_tx_init();
	while (1){
		char *buffer = "Hello world";
		int length = strlen(buffer);
		for (char *i = buffer, *end = buffer + length; i != end; i++){
			uart_write(*i);
		}
		uart_write('\n');
		uart_write('\r');
		for (int i = 0; i < 1000000; i++){}
	}
}

