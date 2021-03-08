# paltaOS
Un sistema operativo que estoy haciendo como hobby para aprender programación a bajo nivel, para plataformas intel i386 y compatibles de momento, basado en: https://wiki.osdev.org/Meaty_Skeleton

# Prerequisitos para compilarlo
Software necesario:

          - Un sistema GNU/Linux
          - Las herramientas para trabajar con código en c (gcc, make, etc)
          - Un compilador cruzado (cross compiler) para compilar desde la arquitectura del sistema host a i686-elf 
            (seguir las instrucciones de https://wiki.osdev.org/GCC_Cross-Compiler)
          - El software de emulación qemu 
          - xorriso
          - El ensamblador nasm
          - grub2
          - GNU mtools
          
# Instrucciones para compilarlo y emularlo

```bash
git clone https://github.com/cocolilo/paltaOS.git
cd paltaOS
./build.sh
./qemu.sh
```

O si quiere compilar y emularlo en qemu con un solo script:

```bash
./test.sh
```

También puede crear una imagen ISO para probarlo en un computador real:

```bash
./iso.sh`
```
