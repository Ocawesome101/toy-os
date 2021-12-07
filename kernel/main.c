#include "drivers/vga.h"
#include "arch/x86/isr.h"
#include "arch/x86/idt.h"
#include "drivers/keyboard.h"
#include "kapi.h"

void kernel_start() {
  clear_screen();
  putstr_at("Kernel v0.\n", 0, 0);
  kprintf("a number: %d\n", 42);
  kprintf("a string: %s\n", "text");
  isr_install();
  //init_timer(1);
  // enable interrupts
  asm volatile("sti");
  init_keyboard();
  char input[255];
  while (1) {
    //putstr("$ ");
    
  }
}
