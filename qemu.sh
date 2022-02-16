#!/bin/sh

#emula el sistema operativo usando la imagen iso generada
set -e
. ./iso.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom paltaos.iso
