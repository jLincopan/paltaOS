#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/paltaos.kernel isodir/boot/paltaos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "paltaos" {
	multiboot /boot/paltaos.kernel
}
EOF
grub-mkrescue -o paltaos.iso isodir
