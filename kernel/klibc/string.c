#include "string.h"

// reverse a string
char* strrev_i(char* s, int len) {
  int a = 0, b = len - 1;
  char ta, tb;
  len /= 2;
  for (int i = 0; i < len; i++) {
    ta = s[a];
    tb = s[b];
    s[a] = tb;
    s[b] = ta;
    a += 1;
    b -= 1;
  }
  return s;
}

char* strrev(char* c) {
  int len = strlen(c);
  return strrev_i(c, len);
}

char* itoa(int n, char* s) {
  int i = 0, sign = n;
  if (n < 0) n = -n;
  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0) s[i++] = '-';
  s[i] = '\0';

  return strrev(s);
}

int strlen(char* s) {
  int i = 0;
  while (s[i] != '\0') ++i;
  return i;
}

int strcmp(char* a, char* b) {
  int i;
  for (i = 0; a[i] == b[i]; i++) {
    if (a[i] == '\0') return 0;
  }
  return a[i] - b[i];
}

char* strtok_r(char* s, char delim, strtok_Save* saveptr) {
  if (s == 0) {
    s = saveptr->s;
  } else {
    saveptr->s = s;
    saveptr->o = 0;
  }
  int i;
  // skip delimiters
  for (i = saveptr->o; s[i] == delim; i++) {}
  // hax
  for ( ; s[i] != '\0' && s[i] != delim; i++) {}
  s[i] = '\0';
  saveptr->o = i+1;
  
  return (char*) s + i;
}
