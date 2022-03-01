;;;Imprime en pantalla lo que esté en bx
imprimir_cadena:
    pusha           ; almacenando los valores en los registros en el stack

imprimir_caracter:
	mov al, [bx]    ; movemos el primer caracter en bx hacia al
	cmp al, 0       ; comparamos el caracter con el número 0
	je fin_funcion  ; si lo que hay en al es igual a 0, saltamos a la sección
		            ; fin_funcion
	int 0x10
	add bx, 1 ; nos movemos un byte hacia adelante en memoria 
	jmp imprimir_caracter ; volvemos al principio de la "función"

fin_funcion:
    popa            ; restauramos los valores anteriores
    ret