#!/bin/sh

#Script para automatizar la instalación de dependencias y el
#compilador cruzado necesarios para compilar y emular paltaOS

BIN_VER="2.38"
GCC_VER="11.2.0"
SOURCE="$HOME/opt/source"
TARGET="i686-elf"
PREFIX="$HOME/opt/cross"

echo -e "\nVersión de binutils a instalar: $BIN_VER"
echo "Versión de gcc a instalar: $GCC_VER"
echo "Arquitectura objetivo para el compilador cruzado: $TARGET"
echo "Directorio para los archivos fuente: $SOURCE"
echo "Directorio para los binarios: $PREFIX"
echo -e "\nInstalando dependencias para compilar paltaOS...\n"

. /etc/os-release

if [ "$ID" = "fedora" ]; then
	sudo dnf install gcc make bison flex gmp-devel libmpc-devel mpfr-devel texinfo nasm qemu-system-x86 xorriso
elif [ "$ID" = "ubuntu" ] || ["$ID" = "debian"]; then
	sudo apt install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo qemu-system-x86 xorriso nasm
elif [ "$ID" = "arch" ] || ["$ID" = "manjaro"]; then
	sudo pacman -Syu base-devel gmp libmpc mpfr qemu-system-x86_64 xorriso nasm
fi

mkdir -p $PREFIX
mkdir -p $SOURCE

echo -e "\nDescargando archivos fuente de binutils $BIN_VER\n"
wget -nd -np -p -c -t 0 --timeout=60 --waitretry=60 https://ftp.gnu.org/gnu/binutils/binutils-$BIN_VER.tar.xz -P $SOURCE/
while [ $? -ne 0 ]; do
	wget -nd -np -p -c -t 0 --timeout=60 --waitretry=60 https://ftp.gnu.org/gnu/binutils/binutils-$BIN_VER.tar.xz -P $SOURCE/
done

echo -e "\nDescargando archivos fuente de gcc $GCC_VER\n"
wget -nd -np -p -c -t 0 --timeout=60 --waitretry=60 https://ftp.gnu.org/gnu/gcc/gcc-$GCC_VER/gcc-$GCC_VER.tar.xz -P $SOURCE/
while [$? -ne 0 ]; do
	wget -nd -np -p -c -t 0 --timeout=60 --waitretry=60 https://ftp.gnu.org/gnu/gcc/gcc-$GCC_VER/gcc-$GCC_VER.tar.xz -P $SOURCE/
done

echo -e "\nDescomprimiendo archivos fuente\n"
cd $SOURCE/
tar -Jxvf binutils-$BIN_VER.tar.xz
tar -Jxvf gcc-$GCC_VER.tar.xz

echo -e "\nCompilando binutils $BIN_VER\n"
mkdir build-binutils
cd build-binutils
../binutils-$BIN_VER/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
echo -e "\nInstalando binutils $BIN_VER en el directorio designado para los binarios\n"
make
make install

echo -e "\nCompilando gcc $GCC_VER\n"
cd $SOURCE/
mkdir build-gcc
cd build-gcc
../gcc-$GCC_VER/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
echo -e "\ninstalando gcc $GCC_VER en el directorio designado para los binarios\n"
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc

echo -e "Terminado\n"
