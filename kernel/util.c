// some utilities

#include "util.h"

// simple memory copier
// **not memcpy**
int memcopy(char* a, char* b, int len) {
  for (int i = 0; i < len; i++) {
    *(b + i) = *(a + i);
  }
}

// reverse a string
int sreverse(char* str, int len) {
  int a = 0, b = len - 1;
  char ta, tb;
  len /= 2;
  for (int i = 0; i < len; i++) {
    ta = str[a];
    tb = str[b];
    str[a] = tb;
    str[b] = ta;
    a += 1;
    b -= 1;
  }
}

int tostring(int n, char* str) {
  int i = 0, sign = n;
  if (n < 0) n = -n;
  do {
    str[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0) str[i++] = '-';
  str[i] = '\0';

  sreverse(str, i);
}
