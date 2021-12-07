#include "ports.h"

unsigned char port_rbyte(unsigned short port) {
  unsigned char result;
  // inline assembly *vomit*
  asm("in %%dx, %%al" : "=a" (result) : "d" (port));
  return result;
}

void port_wbyte(unsigned short port, unsigned char data) {
  asm("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned short port_rword(unsigned short port) {
  unsigned short result;
  asm("in %%dx, %%ax" : "=a" (result) : "d" (port));
  return result;
}

void port_wword(unsigned short port, unsigned short data) {
  asm("out %%ax, %%dx" : : "a" (data), "d" (port));
}
