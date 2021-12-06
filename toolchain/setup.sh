#!/bin/bash
# set up a GCC 11.2.0 toolchain

set -ex

# binutils
wget -c https://ftp.gnu.org/gnu/binutils/binutils-2.37.tar.xz
unxz binutils-2.37.tar.xz
tar xf binutils-2.37.tar
cd binutils-2.37
mkdir -p build && cd build
../configure --target=i386-elf --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=/usr/local/i386elf
make all
sudo make install

# GCC
wget -c https://ftp.gnu.org/gnu/gcc/gcc-11.2.0/gcc-11.2.0.tar.xz
unxz gcc-11.2.0.tar.xz
tar xf gcc-11.2.0.tar
cd gcc-11.2.0
mkdir -p build && cd build
../configure --target=i386-elf --prefix=/usr/local/i386elf --disable-nls --disable-libssp --enable-languages=c --without-headers
make all-gcc
sudo make install-gcc
