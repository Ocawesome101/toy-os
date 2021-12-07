#ifndef KAPI_H
#define KAPI_H

#define PAGE_SIZE 4096
#define PAGES 32768

void* kmalloc(int size);
int kfree(void* ptr);
int kprintf(char* format, ...);
int kpanic(char* format, ...);

#endif
