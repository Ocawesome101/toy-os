#!/bin/bash
# new, better setup script

set -e

target="i386"
buildgcc=1
buildbinutils=1
buildgdb=1

baseurl="https://ftp.gnu.org/gnu"

GCC_VERSION=${GCC_VERSION:-"11.2.0"}
BINUTILS_VERSION=${BINUTILS_VERSION:-"2.37"}
GDB_VERSION=${GDB_VERSION:-"11.1"}

gccdir="gcc-$GCC_VERSION"
binutilsdir="binutils-$BINUTILS_VERSION"
gdbdir="gdb-$GDB_VERSION"

gccurl="$baseurl/gcc/$gccdir/$gccdir.tar.xz"
binutilsurl="$baseurl/binutils/$binutilsdir.tar.xz"
gdburl="$baseurl/gdb/$gdbdir/$gdbdir.tar.xz"

# dlex URL
# download and extract the relevant .tar.xz file, if necessary
dlex () {
  filename=$(basename "$1")
  if ! [ -e "$filename" ]; then
    wget -c "$1" -O "$filename"
  fi
  tar xJf "$filename"
}

while [ "$1" ]; do
  case "$1" in
    i386|i486|i586|i686)
      target=$1
      ;;
    nogcc)
      unset buildgcc
      ;;
    nobinutils)
      unset buildbinutils
      ;;
    nogdb)
      unset buildgdb
      ;;
    help)
      cat << EOF
usage: setup.sh ARG ...
valid arguments:
  i[3456]86:  set target cpu arch
  nogcc:      do not build gcc
  nobinutils: do not build binutils
  nogdb:      do not build gdb
  help:       print this text

environment variables:
  GCC_VERSION: the version of gcc to build, defaults to 11.2.0
  BINUTILS_VERSION: the version of binutils to build, defaults to 2.37
  GDB_VERSION: the version of gdb to build, defaults to 11.1
EOF
      exit 0
      ;;
    *)
      printf "\e[97;101merror\e[39;49m bad argument: \`%s\`\n" "$1"
      printf "try passing 'help'\n"
      exit 1
      ;;
  esac
  shift
done

target="$target-elf"
prefix="/usr/local/$target"
printf "using target $target\n"

# prep DIR URL
prep () {
  rm -rf "$1"
  dlex "$2"
  cd "$1"
  mkdir -p build && cd build
}

# build GCC
if [ "$buildgcc" == "1" ]; then
  prep "$gccdir" "$gccurl"
  ../configure --target=$target --prefix=$prefix --disable-nls --disable-libssp --enable-languages=c --without-headers
  make all-gcc -j$(nproc)
  printf "\a"
  sudo make install
fi

if [ "$buildbinutils" == "1" ]; then
  prep "$binutilsdir" "$binutilsurl"
  ../configure --target=$target --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$prefix
  make all -j$(nproc)
  printf "\a"
  sudo make install
fi

if [ "$buildgdb" == "1" ]; then
  prep "$gdbdir" "$gdburl"
  ../configure --target=$target --prefix=$prefix --program-prefix=$target-
  make -j$(nproc)
  printf "\a"
  sudo make install
fi

printf "\e[94mDONE\e[39m\n"
printf "\e[97mensure that \e[93m$prefix/bin\e[97m is in your \e[92m\$PATH\e[39m\n"
