#include <stdio.h>
#include <stdlib.h>
#include "coord_list.h"
#include "terminal.h"
#include "game.h"

int main(){
  setvbuf(stdout, NULL, _IONBF, 0);
  game_init();
  game_start();
  game_quit();
  return 0;
}
