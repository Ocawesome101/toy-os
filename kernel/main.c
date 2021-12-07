#include "drivers/vga.h"
#include "util.h"
#include "arch/x86/isr.h"
#include "arch/x86/idt.h"
#include "drivers/keyboard.h"

void main() {
  clear_screen();
  putstr_at("Welcome.\n", 0, 0);
  isr_install();
  //init_timer(1);
  // enable interrupts
  asm volatile("sti");
  init_keyboard();
}
