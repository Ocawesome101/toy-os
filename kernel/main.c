#include "video.c"

void main() {
  *(char*)(0xb8000) = 'X';
  vid_clear();
  vid_writeAt(0, "Hello, kernel world!");
}
