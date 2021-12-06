#include "drivers/vga.h"

void main() {
  //vga_set_raw_position(vga_get_raw_position(), 'X', 0x1f);
  clear_screen();
  putstr_at("Hello, kernel world!", 0, 0);
}
