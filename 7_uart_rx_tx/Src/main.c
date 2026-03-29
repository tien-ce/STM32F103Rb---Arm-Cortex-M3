#include "string.h"
#include "uart.h"

int main (void) {
	uart2_rx_tx_init();
	while (1){
//		char *buffer = "Hello world";
//		int length = strlen(buffer);
//		for (char *i = buffer, *end = buffer + length; i != end; i++){
//			uart_write(*i);
//		}
//		uart_write('\n');
//		uart_write('\r');
		char c = uart_read();
		if (c == '\r'){
			uart_write('\r');
			uart_write('\n');
		}
		else
		{
			uart_write(c);
		}
	}
}

