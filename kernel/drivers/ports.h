#ifndef PORTS_H
#define PORTS_H

unsigned char port_rbyte(unsigned short port);
void port_wbyte(unsigned short port, unsigned char data);
unsigned short port_rshort(unsigned short port);
void port_wshort(unsigned short port, unsigned short data);

#endif
