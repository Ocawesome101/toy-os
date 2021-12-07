#ifndef MEM_H
#define MEM_H

void memcpy(char* source, char* dest, int len);
void memset(char* dest, char val, unsigned int len);

void* malloc(int size);
int free(void* ptr);

#endif
