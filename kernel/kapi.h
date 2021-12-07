#ifndef KAPI_H
#define KAPI_H

#define PAGE_SIZE 4096
#define PAGES 32768
extern unsigned int* __stack_chk_guard;
extern void __stack_chk_fail(void);

void* kmalloc(int size);
int kfree(void* ptr);
int kprintf(char* format, ...);
int kpanic(char* format, ...);

#endif
