#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void) {
	terminal_inicializar();
	printf("Hello, kernel World!\n");
}
