#include "keyboard.h"
#include "scancodes.h"
#include "ports.h"
#include "../arch/x86/isr.h"
#include "vga.h"

char input[INPUTBUFSIZE];
int inpos = 0;

int shifted = 0;
static void keyboard_callback(registers_t regs) {
  u8 scancode = port_rbyte(0x60);
  char c = getchar(scancode, shifted);
  if (c == '\x08') {
    delchar();
    input[inpos--] = '\0';
    if (inpos < 0) inpos = INPUTBUFSIZE - 1;
  } else if (c) {
    putchar((input[inpos++] = c));
    if (inpos == INPUTBUFSIZE) inpos = 0;
  } else if (scancode == 0x2A) {
    shifted = 1;
  } else if (scancode == 0xAA) {
    shifted = 0;
  }
}

void init_keyboard() {
  register_interrupt_handler(IRQ1, keyboard_callback);
}
