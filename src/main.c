#include <stdio.h>
#include <stdlib.h>
#include "terminal.h"

int main(){
  termsize size = {0};
  int i;
  printf("Hello World.\n");
  size = get_terminal_size();
  printf("Terminal size: %dx%d\n", size.col, size.row);
  system("clear");
  for(i = 0; i < size.col && i < size.row; i++)
    puts_at(i,i,"*",1);
  return 0;
}
