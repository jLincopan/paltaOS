	;Seteando modo de video
	mov ah, 0x00
	mov al, 0x03
	int 0x10

	mov bx, cadena 	; cargando la cadena en memoria
	call imprimir_cadena
	mov bx, cadena2
	call imprimir_cadena
	push 'x'
	call imprimir_caracter
	push 'D'
	call imprimir_caracter
	hlt
	
    cadena: db 'hola k ase1', 0xa, 0xd, 0
    cadena2: db 'hola k ase2', 0
	%include 'imprimir_cadena.asm'
	%include 'leer_disco.asm'

    times 512-($-$$) db 0