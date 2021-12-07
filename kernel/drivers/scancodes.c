#include "scancodes.h"

// scancode -> ASCII map (unshifted version)
char chars_unshifted[256] =
  "\0\0331234567890-=\x08\tqwertyuiop[]\n\0asdfghjkl;'`\0\\zxcvbnm,./\0\0\0 ";

// scancode -> ASCII map (shifted version)
char chars_shifted[256] =
  "\0\033!@#$%^&*()_+\x08\tQWERTYUIOP{}\n\0ASDFGHJKL:\"~\0|ZXCVBNM<>?\0\0\0 ";

char getchar(char scancode, int shifted) {
  if (shifted) return chars_shifted[scancode];
  else return chars_unshifted[scancode];
}
