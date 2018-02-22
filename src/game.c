#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "terminal.h"
#include "game.h"
#include "coord_list.h"

static CoordList snake = {0}, food = {0};
static unsigned int delay = 50000;
static int cols = 0, rows = 0;
static int score = 0, direction = 0;
static int key_lock = 0, draw_lock = 0, stopped = 0;

static void update(int);
static void capture_key(void);
static void draw_food();
static void draw_snake(Coord);
static void fail();
static void make_food();
static Coord next_coord(Coord, int);
static void snake_move(CoordList*, int);
static void snake_extend(CoordList*, int);

void game_init(){
  int i =0;
  struct sigaction sa;

  srand(time(NULL));
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
  make_food();
  update(0);
  capture_key();
}

void game_quit(){
  stopped = 1;
  list_clear(&snake);
  list_clear(&food);
  signal(SIGALRM, SIG_IGN);
  printf("\e[2J\e[H");
}

void update(int sig){
  CoordList* psnake; psnake = &snake;
  Coord next;
  char buffer[512] = {0};
  next = next_coord(*psnake->head, direction);
  sprintf( buffer,
           "%dx%d h: (%d,%d) l:%3d spd:%3.1fms",
          cols, rows,
          psnake->head->x, psnake->head->y,
          list_len(psnake),
          (float)delay/1000);
  if(!draw_lock){
    draw_lock = 1;
    printf("\e[2J\e[H");
    puts_at(1,1, buffer);
    if( list_include(psnake, next.x, next.y) ||
        next.x < 0 || next.y < 0 ||
        next.x >= (cols/2) || next.y >= rows){
      // u fail
      fail();
    } else {
      if(list_include(&food, next.x, next.y)){
        snake_extend(psnake, direction);
        make_food();
      } else {
        snake_move(psnake, direction);
      }
      key_lock = 0;
      list_each(psnake, draw_snake);
      list_each(&food, draw_food);
      draw_lock = 0;
    }
  }
  if(!stopped)
    ualarm(delay, 0);
}

void draw_snake(Coord coord){
  puts_at((coord.x)*2, coord.y, "■");
}

void draw_food(Coord coord){
  puts_at((coord.x)*2, coord.y, "★");
}

void snake_extend(CoordList *_snake, int dir){
  Coord next, *temp; temp = 0x0;
  next = next_coord(*_snake->head, direction);
  temp = list_del(&food, next.x, next.y);
  list_add(_snake, next.x, next.y);
  if(temp){ free(temp); }
}

void snake_move(CoordList *_snake, int dir){
  Coord next, *temp; temp = 0x0;
  next = next_coord(*_snake->head, direction);
  list_add(_snake, next.x, next.y);
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

void capture_key(){
  int dir = -1, flag = 0;
  char ch;
  while(!stopped){
    ch = getch();
    if( ch == '\e'){ flag = 1; }
    if( ch == '[' && flag == 1 ){ flag = 2; }
    if(flag == 2){
      switch(ch){
        case 'A': // up
          dir = 3;
          break;
        case 'B': // down
          dir = 1;
          break;
        case 'C': // right
          dir = 0;
          break;
        case 'D': // left
          dir = 2;
          break;
        default:
          dir = -1;
          break;
      }
      if(dir >= 0 && (dir ^ direction) != 2 && !key_lock){
        key_lock = 1;
        direction = dir;
      }
    }
    if(ch == 'q'){ stopped = 1; break; }
  }
}

void make_food(){
  int x,y;
  do {
    x = rand() % cols /2;
    y = rand() % rows;
  } while(list_include(&food, x, y));

  list_add(&food, x, y);
}

void fail(){
  int x,y;
  stopped = 1;
  x = cols / 2 - 7;
  y = rows / 2;
  puts_at(x,y-1,"************");
  puts_at(x,y  ,"* u failed *");
  puts_at(x,y+1,"************");
}
