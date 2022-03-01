; Sector de arranque simple


	org 0x7c00 		; especificamos la dirección en memoria desde la que
		   			; NASM asumirá que se carga el bootloader a 0x7c00 
		   			; (que es la dirección en que la bios carga el 
		   			; bootloader) para poder usar offsets relativos en este

	;Seteando modo de video
	mov ah, 0x00
	mov al, 0x03
	int 0x10

	mov ah, 0x0e 	; int 10/ ah 0x0e BIOS telepype output
	mov bx, cadena 	; cargando la dirección de memoria en que se
			     	; encuentra "cadena" al registro bx
	call imprimir_cadena
	mov bx, cadena2
	call imprimir_cadena
	jmp bucle
	
	%include 'imprimir_cadena.asm'

cadena: db "probandoooo", 0xA, 0xD, 0 ; la cadena a imprimir, termina en 
				      				  ; cero para poDER distinguir cuando termina
cadena2: db "hola k ase", 0

bucle:
	jmp $ 			;bucle que salta siempre acá!
	times 510-($-$$) db 0 ;relleno para completar 512 bits 
	dw 0xaa55 		;número mágico (boot magic number)
