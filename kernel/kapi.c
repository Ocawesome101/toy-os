// some kernel API functions

#include "kapi.h"
#include "drivers/vga.h"
#include "klibc/string.h"

// very simple memory allocator
// each bit in this array marks a single page as used or free.
char used[PAGES/8];

int isfree(unsigned int i) {
  int byte = i / 8;
  return ((used[byte] & 2^(i-(byte*8))) != 0);
}

int flipstatus(unsigned int i) {
  int byte = i / 8;
  used[byte] ^= 2^(i-(byte*8));
}

void* kmalloc(int size) {
  int npages = size / PAGE_SIZE + 1;
  int contig = 0, offset = 0;
  for (unsigned int i = 0; i < PAGES && contig < npages; i++) {
    if (isfree(i)) contig += 1;
    else contig = 0, offset = i;
  }
  if (contig == 0) {
    kpanic("Out of free pages for malloc()!");
  }
}

int kfree(void* ptr) {
}

int vkprintf(char* format, __builtin_va_list argp) {
  while (*format != '\0') {
    if (*format == '%') {
      format++;
      if (*format == '%') {
        putchar('%');
      } else if (*format == 'c') {
        char c = __builtin_va_arg(argp, int);
        putchar(c);
      } else if (*format == 'd') {
        char num[256];
        itoa(__builtin_va_arg(argp, int), &num);
        putstr(num);
      } else if (*format == 's') {
        putstr(__builtin_va_arg(argp, char*));
      } else {
        putstr("kprintf format not implemented\n");
      }
    } else {
      putchar(*format);
    }
    format++;
  }
  __builtin_va_end(argp);
}

int kprintf(char* format, ...) {
  // TODO: don't use GCC builtins
  __builtin_va_list argp;
  __builtin_va_start(argp, format);
  vkprintf(format, argp);
}

int vklog(char* format, __builtin_va_list argp) {
  putstr("[k] ");
  vkprintf(format, argp);
}

int klog(char* format, ...) {
  __builtin_va_list argp;
  __builtin_va_start(argp, format);
  vklog(format, argp);
}

int kpanic(char* format, ...) {
  __builtin_va_list argp;
  __builtin_va_start(argp, format);
  // disable interrupts
  asm volatile("cli");
  klog("KERNEL PANIC\n");
  klog(format, argp);
}
