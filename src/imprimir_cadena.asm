imprimir_caracter:
	push ax
	push bp
	mov bp, sp

	mov ah, 0x0e
	mov al, [bp+6]
	int 0x10
	
	pop ax
	pop bp
	ret

;;;Imprime en pantalla lo que esté en bx
imprimir_cadena:
    pusha           ; almacenando los valores en los registros en el stack
	mov ah, 0x0e 	; int 10/ ah 0x0e BIOS telepype output
	
	.INICIO_BUCLE:
	mov al, [bx]    ; movemos el primer caracter en bx hacia al
	cmp al, 0       ; comparamos el caracter con el número 0
	je .FIN_BUCLE   ; si lo que hay en al es igual a 0, saltamos a la sección
		        	; fin_funcion ya que termina la cadena
	int 0x10
	add bx, 1 		; nos movemos un byte hacia adelante en memoria 
	jmp .INICIO_BUCLE ; volvemos al principio de la "función"

	.FIN_BUCLE:
    popa            ; restauramos los valores anteriores
    ret