# paltaOS
Un sistema operativo que estoy haciendo como hobby para aprender programación a bajo nivel, para plataformas intel i386 y compatibles de momento, basado en: \
-https://wiki.osdev.org/Meaty_Skeleton \
-http://littleosbook.github.io

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

-Instalar el software necesario, si está en otra distro que no sea ubuntu hay que buscar los comandos para instalar los paquetes:
```bash
sudo apt install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo qemu-system-i386 nasm
```
-Seguir las instrucciones de https://wiki.osdev.org/GCC_Cross-Compiler para tener un compilador cruzado que produzca binarios
 para la arquitectura que se usa (no menor que i386)
 
-Clonar el repositorio:
```bash
git clone https://github.com/jLincopan/paltaOS.git
```
-Cambie la variable COMPILADOR que guarda la ubicación de los binarios del compilador cruzado, esta variable está ubicada
 en el script config.sh. Si se siguió al pie de la letra ese tutorial debería ser algo así como $HOME/opt/cross/bin, si la
 cambiaste debería ser la ubicación en la que hayas instalado tu compilador
 
-Para compilar:
```bash
cd paltaOS
./build.sh
```
-Para emular el sistema en qemu (esto compila antes de emular)
```bash
./qemu.sh
```
