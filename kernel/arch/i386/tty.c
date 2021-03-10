#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/vga.h>
#include <kernel/io.h>

/* Los puertos I/O VGA */
#define FB_PUERTO_COMANDOS 0x3D4
#define FB_PUERTO_DATOS    0x3D5
/* Los comandos I/O VGA  */
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND  15

/* el "framebuffer" vga solo puede mostrar una pantalla
de 80x25 a la vez */

static const size_t VGA_ANCHO = 80;
static const size_t VGA_ALTO = 25;

/**se comunica con él usando "memory mapped I/O"
 * cada espacio esta compuesto de 16 bits, por lo
 * que el total de bits que tiene esta memoria es de
 * 80x25x16 = 32000 bits = 3.25 kB
 * La memoria empieza en la dirección 0x000B8000
 * y cada espacio de la pantalla se alcanza sumandole 
 * 16 a esa dirección de memoria
**/
static uint16_t* const MEMORIA_VGA = (uint16_t*) 0x000B8000;

static size_t fila;
static size_t columna;
static uint8_t color_fondo;
static uint16_t posicion_cursor = 0;
static uint16_t* terminal_buffer;

/*mueve el cursor a la posición x (recordar que esto es un array
  donde 80 elementos seguidos representan una fila)
  xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx
  fila 1   fila 2   fila 3   fila 4   etc*/
void terminal_moverCursor(uint16_t posicion) {
	outb(FB_PUERTO_COMANDOS, FB_HIGH_BYTE_COMMAND);
	outb(FB_PUERTO_DATOS,    ((posicion >> 8) & 0x00FF));
	outb(FB_PUERTO_COMANDOS, FB_LOW_BYTE_COMMAND);
	outb(FB_PUERTO_DATOS,    posicion & 0x00FF);
}

/*inicializa la terminal, llenándola de espacios vacíos con el
 color de fondo especificado en color_fondo*/ 
void terminal_inicializar(void) {
	fila = 0;
	columna = 0;
	color_fondo = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = MEMORIA_VGA;
	for (size_t y = 0; y < VGA_ALTO; y++) {
		for (size_t x = 0; x < VGA_ANCHO; x++) {
			const size_t index = y * VGA_ANCHO + x;
			terminal_buffer[index] = vga_entry(' ', color_fondo);
		}
	}
}

/*cambia el color de fondo, no pinta la pantalla, solo cambia el valor
  del color a usarse como fondo después de llamar esta función*/
void terminal_cambiarFondo(uint8_t color) {
	color_fondo = color;
}

/*posiciona el caracter c en la posicion x,y de la pantalla con el color
  especificado en la variable "color"*/
void terminal_caracterXY(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_ANCHO + x;
	terminal_buffer[index] = vga_entry(c, color);
}

/*solo verifica si hay que resetear la posición x o y del caracter a escribir y 
  llama a la función que posiciona realmente los carácteres*/
void terminal_posicionarCaracter(char c) {
	unsigned char uc = c;

	if (uc == '\n') {
		fila++;
		posicion_cursor = posicion_cursor - columna + 80 - 1;
		columna = 0;
		terminal_moverCursor(posicion_cursor);
	} else {
		terminal_caracterXY(uc, color_fondo, columna, fila);
		if (++columna == VGA_ANCHO) {
			columna = 0;
			if (++fila == VGA_ALTO)
				fila = 0;
		}
	}
}

void terminal_imprimirCadena(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_posicionarCaracter(data[i]);
	//movemos al cursor la cantidad de carácteres que tenga la cadena
	posicion_cursor = posicion_cursor + (uint16_t)strlen(data);
	terminal_moverCursor(posicion_cursor);
}
