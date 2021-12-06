// basic video output

#define WIDTH 80
#define HEIGHT 24

#define vga_putcharAt(i,c) *(vgamem + i*2) = c;

void vid_writeAt(int n, char* str) {
  char* vgamem = (char*) 0xb8000;
  for (int i = 0; str[i] != '\0'; i++) {
    vga_putcharAt(n + i, *(str + i));
  }
}

void vid_clear() {
  char* vgamem = (char*) 0xb8000;
  for (int i = 0; i < WIDTH * HEIGHT; i++) {
    *(vgamem + i*2) = ' ';
  }
}
