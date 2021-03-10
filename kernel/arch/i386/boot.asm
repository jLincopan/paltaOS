extern kernel_main
global _start             ; the entry symbol for ELF

MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant.section .multiboot
FLAGS        equ 0x0            ; multiboot flags.long MAGIC
CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum

section .text:                  ; start of the text (code) section
align 4                         ; the code must be 4 byte aligned
dd MAGIC_NUMBER             ; write the magic number to the machine code,
dd FLAGS                    ; the flags,
dd CHECKSUM                 ; and the checksum

_start:                         ; the loader label (defined as entry point in linker script)

  call kernel_main

.loop:
  jmp .loop                   ; loop forever