#include "drivers/vga.h"
#include "arch/x86/isr.h"
#include "arch/x86/idt.h"
#include "drivers/keyboard.h"
#include "kapi.h"

void kernel_start() {
  clear_screen();
  klog("Kernel v0.\n", 0, 0);
  klog("a number: %d\n", 42);
  klog("a string: %s\n", "text");
  klog("a char: %c\n", 'b');
  klog("a bad format: %e");
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
