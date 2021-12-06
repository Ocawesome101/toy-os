#!/bin/bash
# set up a GCC 11.2.0 toolchain

set -ex

while [ "$1" ]; do
  case "$1" in
    binutils)
      # binutils
      wget -c https://ftp.gnu.org/gnu/binutils/binutils-2.37.tar.xz
      unxz binutils-2.37.tar.xz
      tar xf binutils-2.37.tar
      cd binutils-2.37
      mkdir -p build && cd build
      ../configure --target=i386-elf --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=/usr/local/i386elf
      make all
      sudo make install
      ;;

    gcc)
      # GCC
      wget -c https://ftp.gnu.org/gnu/gcc/gcc-11.2.0/gcc-11.2.0.tar.xz
      unxz gcc-11.2.0.tar.xz
      tar xf gcc-11.2.0.tar
      cd gcc-11.2.0
      mkdir -p build && cd build
      ../configure --target=i386-elf --prefix=/usr/local/i386elf --disable-nls --disable-libssp --enable-languages=c --without-headers
      make all-gcc
      sudo make install-gcc
      ;;

    gdb)
      # GDB
      wget -c https://ftp.gnu.org/gnu/gdb/gdb-11.1.tar.xz
      unxz gdb-11.1.tar.xz
      tar xf gdb-11.1.tar
      cd gdb-11.1
      mkdir -p build && cd build
      ../configure --target=i386-elf --prefix=/usr/local/i386elfgcc --program-prefix=i386-elf-
      make
      sudo make install
      ;;
  esac
  shift
done
