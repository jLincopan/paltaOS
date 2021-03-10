#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

void terminal_inicializar(void);
void terminal_posicionarCaracter(char c);
void terminal_imprimirCaracter(const char* data, size_t size);
void terminal_imprimirCadena(const char* data);

#endif
