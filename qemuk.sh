#!/bin/sh

#emula solo el kernel del sistema operativo
. ./build.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) -kernel sysroot/boot/paltaos.kernel