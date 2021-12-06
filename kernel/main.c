#include "drivers/vga.h"
#include "util.h"

void main() {
  //vga_set_raw_position(vga_get_raw_position(), 'X', 0x1f);
  clear_screen();
  char str[255];
  putstr_at("Hello, kernel world!\nTest some more!\n", 0, 0);
  for (int i = 0; i < 256; i++) {
    tostring(i, &str);
    putstr(str);
    putstr("\n");
  }
}
