#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

void terminal_inicializar(void);
void terminal_posicionarCaracter(char c);
void terminal_imprimirCadena(const char* data, size_t size);
#endif
