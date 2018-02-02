#include "terminal.h"

termsize get_terminal_size(){
  struct winsize w;
  termsize result;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  result.row = w.ws_row;
  result.col = w.ws_col;
  return result;
}
