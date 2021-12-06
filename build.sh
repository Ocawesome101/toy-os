#!/bin/bash

set -ex
CC=i386-elf-gcc
LD=i386-elf-ld
GDB=i386-elf-gdb

# The files to compile.
FILES=(kernel/drivers/*.c kernel/main.c)

cd bootloader
nasm -f bin boot.asm -o /tmp/boot.bin
cd ..

i=0
for file in "${FILES[@]}"; do
  $CC -g -ffreestanding -c $file -o /tmp/$(basename $file).o
  FILES[i]=/tmp/$(basename $file).o
  i+=1
done

nasm kernel/entry.asm -f elf -o /tmp/entry.o
$LD -Ttext 0x1000 --oformat binary /tmp/entry.o ${FILES[@]} -o /tmp/kernel.bin


cat /tmp/boot.bin /tmp/kernel.bin > osimage.bin


if [ "$1" = "run" ]; then
  if [ "$2" = "debug" ]; then
    qemu-system-i386 -s -fda osimage.bin & \
      $GDB -ex "target remote localhost:1234" -ex "symbol-file /tmp/kernel.o"
  else
    qemu-system-i386 -s -fda osimage.bin
  fi
fi
