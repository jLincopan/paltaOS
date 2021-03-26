#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/serial.h>

void kernel_main(void) {
	terminal_inicializar();
	printf("Hello, kernel World!\n");
	serial_configurar_puerto(COM1, 1);
	serial_transmitir_cadena(COM1, "*");
	serial_transmitir_cadena(COM1, "**");
	serial_transmitir_cadena(COM1, "***");
	serial_transmitir_cadena(COM1, "****");
	serial_transmitir_cadena(COM1, "*****");
}
