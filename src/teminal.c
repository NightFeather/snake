#include "terminal.h"

termsize get_terminal_size(){
  struct winsize w;
  termsize result;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  result.row = w.ws_row;
  result.col = w.ws_col;
  return result;
}

void puts_at(int row, int col, char* string, int length){
  printf("\e[%d;%dH%.*s", row, col, length, string);
}
