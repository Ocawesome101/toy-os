// basic IO

#include "io.h"
#include "../drivers/keyboard.h"

int read_pos = 0;

char readc() {
  while (input[read_pos] == '\0') {}
  char c = input[read_pos++];
  if (read_pos == INPUTBUFSIZE) read_pos = 0;
  return c;
}

char* readline(char* buf) {
  int i = 0;
  while ((buf[i++] = readc()) != '\n') {}
  // replace trailing newline
  buf[--i] = '\0';
  return buf;
}
