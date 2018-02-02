#include <stdio.h>
#include <stdlib.h>
#include "terminal.h"

int main(){
  termsize size = {0};
  printf("Hello World.\n");
  size = get_terminal_size();
  printf("Terminal size: %dx%d\n", size.col, size.row);
  return 0;
}
