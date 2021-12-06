#!/bin/bash

CC=i386-elf-gcc
LD=i386-elf-ld

cd bootloader
nasm -f bin boot.asm -o /tmp/boot.bin
cd ..


$CC -ffreestanding -c kernel/main.c -o /tmp/kernel.o
nasm kernel/entry.asm -f elf -o /tmp/entry.o
$LD -Ttext 0x1000 --oformat binary /tmp/entry.o /tmp/kernel.o -o /tmp/kernel.bin


cat /tmp/boot.bin /tmp/kernel.bin > osimage.bin


if [ "$1" = "run" ]; then
  qemu-system-x86_64 -fda osimage.bin
fi
