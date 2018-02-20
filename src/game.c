#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "terminal.h"
#include "game.h"
#include "coord_list.h"

static CoordList snake = {0}, food = {0};
static int cols = 0, rows = 0;
static int score = 0, direction = 0;
static int lock = 0, stopped = 0;

static void update(int);
static void draw_snake(Coord);
static void snake_move(CoordList*, int);
//static void snake_extend(CoordList, int);
//static void make_food();
//static void remove_food(Coord);
static Coord next_coord(Coord, int);

void game_init(){
  int i =0;
  struct sigaction sa;

  get_terminal_size(&cols, &rows);

  list_clear(&snake);

  for(i = 0; i < 3; i++)
    list_add(&snake, i, 0);

  sa.sa_handler = update;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sigaction(SIGALRM, &sa, 0x0);
}

void game_start(){
  update(0);
}

void game_quit(){
  stopped = 1;
  list_clear(&snake);
  list_clear(&food);
}

void update(int sig){
  CoordList* psnake = &snake;
  if(!lock){
    lock = 1;
    system("clear");
    snake_move(psnake, direction);
    list_each(psnake, draw_snake);
    lock = 0;
  }
  if(!stopped)
    ualarm(100000, 0);
}

void draw_snake(Coord coord){
  puts_at(coord.x+1, coord.y+1, "*", 1);
}

void snake_move(CoordList *_snake, int dir){
  Coord next, *temp;
  next = next_coord(*_snake->head, direction);
  temp = list_del(&food, next.x, next.y);
  list_add(_snake, next.x, next.y);
  if(!temp)
    temp = list_take(_snake);

  free(temp);
}

Coord next_coord(Coord coord, int direction){
  switch(direction){
    case 0:
      coord.x += 1;
      break;
    case 1:
      coord.y += 1;
      break;
    case 2:
      coord.x -= 1;
      break;
    case 3:
      coord.y -= 1;
  }

  return coord;
}