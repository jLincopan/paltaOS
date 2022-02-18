# paltaOS
Un sistema operativo que estoy haciendo como hobby para aprender programación a bajo nivel, para plataformas intel i386 y compatibles de momento, basado en: \
-https://wiki.osdev.org/Meaty_Skeleton \
-http://littleosbook.github.io

# Prerequisitos para compilarlo
Software necesario:

          - Un sistema GNU/Linux
          - Las herramientas para trabajar con código en c (gcc, make, etc)
          - Un compilador cruzado (cross compiler) para compilar desde la arquitectura del sistema host a i686-elf 
            (seguir las instrucciones de https://wiki.osdev.org/GCC_Cross-Compiler o bien ejecutar el script configuracionInicial.sh)
          - El software de emulación qemu
          - xorriso
          - El ensamblador nasm
          - grub2
          - GNU mtools
          
# Instrucciones para compilarlo y emularlo


-Clonar el repositorio:
```bash
git clone https://github.com/jLincopan/paltaOS.git
```

-Ejecutar el script configuracionInicial.sh. Este script instalará los programas requeridos para trabajar con paltaOS. Además descargará el código fuente de gcc y binutils, lo compilará y lo dejará listo para funcionar como compilador cruzado.
```bash
./configuracionInicial.sh
```

-En caso de que lo anterior falle, instalar manualmente los programas necesarios o seguir las instrucciones de https://wiki.osdev.org/GCC_Cross-Compiler para tener un compilador cruzado que produzca binarios
 para la arquitectura que se usa (no menor que i386), dependiendo de lo que haya fallado.
 Cambie la variable COMPILADOR que guarda la ubicación de los binarios del compilador cruzado, esta variable está ubicada en el script config.sh. Si se siguió al pie de la letra ese tutorial debería ser algo así como $HOME/opt/cross/bin, si la cambiaste debería ser la ubicación en la que hayas instalado los binarios de tu compilador cruzado
 
-Para compilar:
```bash
cd paltaOS
./build.sh
```
-Para emular el sistema en qemu (esto compila antes de emular):
```bash
./qemu.sh
```
-Para emular solo el kernel:
```bash
./qemuk.sh
```