#ifndef STR_H
#define STR_H

char* itoa(int n, char* str);
char* strrev(char* s);
int strlen(char* s);
int strcmp(char* a, char* b);
char* strtok(char* s, char delim);

typedef struct s {
  char* s;
  int o;
} strtok_Save;

#endif
