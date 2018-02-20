#include "terminal.h"

void get_terminal_size(int* cols, int* rows){
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  *rows = w.ws_row;
  *cols = w.ws_col;
}

void puts_at(int col, int row, char* string, int length){
  printf("\e[%d;%dH%.*s", row, col, length, string);
}
