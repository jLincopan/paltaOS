leer_disco:
    mov ah, 0x02
    mov al, 0x01
    int 0x13

    jc leer_disco
    ret

error_disco:
    mov bx, MSJ_ERROR_DISCO
    call imprimir_cadena
    hlt

MSJ_ERROR_DISCO: db 'Error al leer el disco, aiuda', 0