int my_function() {
  return 0xbaba;
}

void main() {
  char* vidmem = (char*) 0xb8000;
  *vidmem = 'X';
}
