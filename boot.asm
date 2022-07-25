; Simple bootloader que usa INT 13 AH2 para leer desde el disco


	org 0x7c00 		; especificamos la dirección en memoria desde la que
		   			; NASM asumirá que se carga el bootloader a 0x7c00 
		   			; (que es la dirección en que la bios carga el 
		   			; bootloader) para poder usar offsets relativos en este

	;; ES:BX offset para cargar los sectores en memoria
	mov bx, 0x1000  ; 
	mov es, bx	; Seteamos registro de segmentos es (solo se puede hacer con otro
				; registro o instrucciones especiales)
	mov bx, 0x0 ; offset 0

	;; Preparación para leer el disco

	mov ch, 0x0		; cylinder 0
	mov cl, 0x02	; Sector desde donde se empieza a leer
	mov dh, 0x0		; head 0
	mov dl, 0x0		; drive 0

	call leer_disco

	mov ax, 0x1000
    mov ds, ax


	jmp 0x1000:0x0

	%include 'imprimir_cadena.asm'
	%include 'leer_disco.asm'
	times 510-($-$$) db 0 ;relleno para completar 512 bits del sector
	dw 0xaa55 		;número mágico (boot magic number)

