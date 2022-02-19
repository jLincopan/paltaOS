//Se usa como base estos tutoriales: -https://wiki.osdev.org/Serial_ports
//                                   -https://en.wikibooks.org/wiki/Serial_Programming/8250_UART_Programming
//Algo más técnico: http://www.roboard.com/Files/Reg/Serial_Port_Registers.pdf

#include <stdio.h>
#include <string.h>
#include <kernel/io/io.h>
#include <kernel/io/serial.h>

void serial_configurar_velocidad(unsigned short divisor, unsigned short com) {
    /*le decimos al hardware del puerto serial que
    vamos a mandar datos, lo que hace que este
    le mande a la CPU un interrupt*/
    outb(SERIAL_PUERTO_ACTIVAR_INTERRUPT(com), 0x00);
    outb(SERIAL_PUERTO_CONTROL_LINEA(com), SERIAL_ACTIVAR_DLAB); //activamos DLAB
    //procedemos a mandar el divisor en dos partes:
    outb(SERIAL_PUERTO_DATOS(com), divisor & 0x00FF); //byte menos significativo
    outb(SERIAL_PUERTO_ACTIVAR_INTERRUPT(com), divisor & 0xFF); //byte más significativo

}

void serial_configurar_linea(unsigned short com) {

    /*0x03 = 00000011, los últimos 2 bits controlan la cantidad
    de bits que se transmiten a la vez: 
    00 = 5 bits, 01 = 6 bits, 10 = 7 bits, 11 = 8bits
    consultar el pdf que hay arriba para más
    información acerca de los demás bits, pero copio un resumen:
    Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
    Content: | d | b | prty  | s | dl  |

    Name 	Description
    d 	Enables (d = 1) or disables (d = 0) DLAB
    b 	If break control is enabled (b = 1) or disabled (b = 0)
    prty 	The number of parity bits to use
    s 	The number of stop bits to use (s = 0 equals 1, s = 1 equals 1.5 or 2)
    dl 	Describes the length of the data
    */

    //consultar el pdf de arriba para ver qué hacen realmente los valores
    //que se mandan acá
    outb(SERIAL_PUERTO_CONTROL_LINEA(com), 0x03); // 8 bits, no parity, one stop bit
    outb(SERIAL_PUERTO_FIFO(com), 0xC7); // Enable FIFO, clear them, with 14-byte threshold
    outb(SERIAL_PUERTO_CONTROL_MODEM(com), 0x0B); // IRQs enabled, RTS/DSR set; RTS = request to send, DSR = Data terminal ready

    //se activa el modo de pruebas (loopback), para saber si funciona bien
    //el puerto serial
    outb(SERIAL_PUERTO_CONTROL_MODEM(com), 0x1E); 

    //Probando el puerto serial, si devuelve el mismo
    //byte que se le envía está bien
    outb(SERIAL_PUERTO_DATOS(com), 0xAE); // enviamos el byte
    if(inb(SERIAL_PUERTO_DATOS(com)) != 0xAE) {
        printf("Error, el puerto no ha sido bien configurado");
        return;
    }
 
   //Si pasa la prueba se activa el modo normal de operaciones
   //(not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
   outb(SERIAL_PUERTO_CONTROL_MODEM(com), 0x0F);
}

void serial_configurar_puerto(unsigned short com, unsigned short divisor) {
    serial_configurar_velocidad(divisor, com);
    serial_configurar_linea(com);
}

unsigned short serial_puedo_transmitir(unsigned short com){
    /* 0x20 = 0010 0000, solo se verifica el bit que indica
    si la línea está disponible: 1 = disponible */
    return inb(SERIAL_PUERTO_ESTADO_DE_LINEA(com)) & 0x20;
}

int serial_puedo_leer(unsigned short com) {
   return inb(SERIAL_PUERTO_ESTADO_DE_LINEA(com)) & 1;
}

void serial_transmitir_caracter(unsigned short com, char dato) {
   while (serial_puedo_transmitir(com) == 0);
   outb(com, dato);
}

void serial_transmitir_cadena(unsigned short com, const char* cadena) {
    for(size_t i = 0; i < strlen(cadena); i++) {
        serial_transmitir_caracter(com, cadena[i]);
        
    }
    serial_transmitir_caracter(com, '\r');
    serial_transmitir_caracter(com, '\n');
}

char serial_leer(unsigned short com) {
   while (serial_puedo_leer(com) == 0) {
       //no hacer nada mientras no se pueda leer datos
   }
   return inb(com);
}