#include "string.h"
#include "../kapi.h"

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

// nonconformant behavior
char* strtok(char* s, char* words[]) {
  words[0] = kmalloc(MAX_TOK_LEN);
  int len = strlen(s);
  int i = 0, alen = 0, word = 0, instr = 0;
  for (i = 0; i < len; i++) {
    if (s[i] == ' ' && alen > 0 && (i+1) < len && instr == 0) {
      words[word][alen] = '\0';
      word++;
      alen = 0;
      words[word] = kmalloc(MAX_TOK_LEN);

      if (word > MAX_WORDS) {
        kpanic("word limit of %d exceeded\n", MAX_WORDS);
      }
    }
  }
}
