OS:	boot.asm kernel.bin
	cat bin/boot.bin bin/kernel.bin > OS.bin
	bochs -q

boot.asm:
	nasm -Isrc src/boot.asm -o bin/boot.bin

kernel.bin:
	nasm -Isrc src/kernel.asm -o bin/kernel.bin

clean:
	rm bin/*