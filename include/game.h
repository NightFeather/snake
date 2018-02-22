
#ifndef __GAME_H__
#define __GAME_H__

#include "coord_list.h"

typedef struct {
  unsigned int delay;
  int cols, rows;
  int length;
  char snake, food;
} GameConfig;

typedef struct {
  CoordList snake , food;
  int score , direction;
  int key_lock , draw_lock , stopped;
} GameState;

void game_init();
void game_start();
void game_quit();

#endif
