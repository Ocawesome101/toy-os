#ifndef STR_H
#define STR_H

#define MAX_WORDS 64
#define MAX_TOK_LEN 64

char* itoa(int n, char* str);
char* strrev(char* s);
int strlen(char* s);
int strcmp(char* a, char* b);
char* strtok(char* s, char* words[]);

#endif
