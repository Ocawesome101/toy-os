// VGA!

#include "ports.h"
#include "vga.h"

int get_offset(int col, int row) { return 2 * (row * VGA_COLS + col); }
int get_offset_row(int offset) { return offset / (2 * VGA_COLS); }
int get_offset_col(int offset) {
  return (offset - (get_offset_row(offset)*2*VGA_COLS))/2;
}

// private functions
int vga_get_raw_position() {
  int position;
  port_wbyte(VGA_CONTROL_REG, VGA_CURSOR_H);
  position = port_rbyte(VGA_DATA_REG) << 8;
  port_wbyte(VGA_CONTROL_REG, VGA_CURSOR_L);
  position += port_rbyte(VGA_DATA_REG);
  return position;
}

int vga_set_raw_position(int pos) {
  port_wbyte(VGA_CONTROL_REG, VGA_CURSOR_H);
  port_wbyte(VGA_DATA_REG, (unsigned char)(pos >> 8));
  port_wbyte(VGA_CONTROL_REG, VGA_CURSOR_L);
  port_wbyte(VGA_DATA_REG, (unsigned char)(pos & 0xFF));
}

int vga_set_at_raw_position(int pos, unsigned char c, unsigned char color) {
  char *vga = (unsigned char*) VGA_ADDRESS;
  int offset = pos * 2;
  vga[offset] = c;
  vga[offset+1] = color;
}

unsigned char vga_pack_color(char fg, char bg) {
  return (bg >> 4) + fg;
}

int vga_get_position() {
  return vga_get_raw_position() * 2;
}

void vga_set_position(int offset) {
  vga_set_raw_position(offset / 2);
}

int vga_set_at_position(char c, int col, int row, unsigned char color) {
  unsigned char *vidmem = (unsigned char*) VGA_ADDRESS;
  if (!color) color = 0x0f;

  if (col >= VGA_COLS || row >= VGA_ROWS) {
    vidmem[2*(VGA_COLS)*(VGA_ROWS)-2] = 'E';
    vidmem[2*(VGA_COLS)*(VGA_ROWS)-1] = 0xf4;
    return get_offset(col, row);
  }

  int offset;
  if (col >=0 && row >= 0) {
    offset = get_offset(col, row);
  } else {
    offset = vga_get_position();
  }

  if (c == '\n') {
    row = get_offset_row(offset);
    offset = get_offset(0, row + 1);
  } else {
    vidmem[offset] = c;
    vidmem[offset+1] = color;
    offset += 2;
  }
  vga_set_position(offset);
  return offset;
}

// public functions
void putstr_at(char* str, int col, int row) {
  int offset;
  if (col >= 0 && row >= 0) {
    offset = get_offset(col, row);
  } else {
    offset = vga_get_position();
    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }

  for (int i = 0; str[i] != 0; i++) {
    offset = vga_set_at_position(str[i], col, row, 0x0f);
    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }
}

void putstr(char* str) {
  putstr_at(str, -1, -1);
}

void clear_screen() {
  int screen_size = VGA_COLS * VGA_ROWS;
  int i;
  char *screen = (unsigned char*) VGA_ADDRESS;

  for (i = 0; i < screen_size; i++) {
    screen[i*2] = ' ';
    screen[i*2+1] = 0x0f;
  }
  vga_set_position(get_offset(0, 0));
}

