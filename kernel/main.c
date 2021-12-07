#include "drivers/vga.h"
#include "util.h"
#include "arch/x86/isr.h"
#include "arch/x86/idt.h"

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
  isr_install();
  __asm__ __volatile__("int $2");
  __asm__ __volatile__("int $3");
}
