//Se usa como base estos tutoriales: -https://wiki.osdev.org/Serial_ports
//                                   -https://en.wikibooks.org/wiki/Serial_Programming/8250_UART_Programming
//Algo más técnico: http://www.roboard.com/Files/Reg/Serial_Port_Registers.pdf

#ifndef INCLUDE_SERIAL_H
    #define INCLUDE_SERIAL_H

    //direcciones comunes de puertos seriales
    #define COM1 0x3F8
    #define COM2 0x2F8
    #define COM3 0x3E8
    #define COM4 0x2E8

    /* Registros de un puerto serial común y corriente en x86
    *DLAB = Divisor Latch Access Bit
    *When this bit is set, offsets 0 and 1 are mapped to the low and high bytes of the Divisor register 
    for setting the baud rate of the port. When this bit is clear, offsets 0 and 1 are mapped to their normal registers. 
    *The DLAB bit only affects port offsets 0 and 1, the other offsets ignore this setting. 
    IO Port Offset 	Setting of DLAB 	Register mapped to this port
    +0                 	    0 	        Data register. Reading this register reads from the Receive buffer. Writing to this register writes to the Transmit buffer.
    +1                 	    0 	        Interrupt Enable Register.
    +0                 	    1 	        With DLAB set to 1, this is the least significant byte of the divisor value for setting the baud rate.
    +1                 	    1 	        With DLAB set to 1, this is the most significant byte of the divisor value.
    +2                 	    - 	        Interrupt Identification and FIFO control registers
    +3                 	    - 	        Line Control Register. The most significant bit of this register is the DLAB.
    +4                 	    - 	        Modem Control Register.
    +5                 	    - 	        Line Status Register.
    +6                 	    - 	        Modem Status Register.
    +7                 	    - 	        Scratch Register. 
    */


    //puertos:

    //Si DLAB está activo, aquí se manda el byte menos significativo del divisor
    #define SERIAL_PUERTO_DATOS(puerto)             (puerto) 
    //Si DLAB está activo, aquí se manda el byte más significativo del divisor
    #define SERIAL_PUERTO_ACTIVAR_INTERRUPT(puerto) (puerto + 1) 

    #define SERIAL_PUERTO_FIFO(puerto)              (puerto + 2)
    #define SERIAL_PUERTO_CONTROL_LINEA(puerto)     (puerto + 3)
    #define SERIAL_PUERTO_CONTROL_MODEM(puerto)     (puerto + 4)
    #define SERIAL_PUERTO_ESTADO_DE_LINEA(puerto)   (puerto + 5)

    //comandos:
    #define SERIAL_ACTIVAR_DLAB    0x80 //10000000 en binario

    //funciones:
    void serial_configurar_velocidad(unsigned short divisor, unsigned short com);
    void serial_configurar_linea(unsigned short com);
    void serial_configurar_puerto(unsigned short com, unsigned short divisor);
    void serial_transmitir(unsigned short com, char dato);
    char serial_leer(unsigned short com);
#endif