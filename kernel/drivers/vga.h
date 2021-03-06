// VGA!

#ifndef VGA_H
#define VGA_H

#define VGA_CONTROL_REG 0x3d4
#define VGA_DATA_REG 0x3d5
#define VGA_CURSOR_H 14
#define VGA_CURSOR_L 15
#define VGA_ADDRESS 0xb8000
#define VGA_ROWS 25
#define VGA_COLS 80

unsigned char vga_pack_color(char fg, char bg);
void clear_screen();
int putchar_at(char c, int col, int row);
void putchar(char c);
void delchar();
void putstr_at(char *str, int col, int row);
void putstr(char *str);

#endif
