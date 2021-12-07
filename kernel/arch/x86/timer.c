#include "timer.h"
#include "../../drivers/vga.h"
#include "../../drivers/ports.h"
#include "../../klibc/string.h"
#include "isr.h"

u32 tick = 0;

static void timer_callback(registers_t regs) {
  tick++;
  putstr("tick: ");

  char tick_ascii[256];
  itoa(tick, &tick_ascii);
  putstr(tick_ascii);
  putstr("\n");
}

void init_timer(u32 freq) {
  register_interrupt_handler(IRQ0, timer_callback);

  u32 divisor = 1193180 / freq;
  u8 low = (u8)(divisor & 0xFF);
  u8 high = (u8)((divisor >> 8) & 0xFF);
  port_wbyte(0x43, 0x36);
  port_wbyte(0x40, low);
  port_wbyte(0x40, high);
}
