#include "../kapi.h"

int memcpy(char* source, char* dest, int len) {
  for (int i = 0; i < len; i++) {
    *(dest + i) = *(source + i);
  }
  return 0;
}

int memset(char* dest, char val, unsigned int len) {
  char* temp = (char*) dest;
  for ( ; len != 0; len--) *temp++ = val;
  return 0;
}

void* malloc(int size) {
  return kmalloc(size);
}

int free(void* ptr) {
  return kfree(ptr);
}
