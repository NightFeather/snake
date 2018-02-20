#include <stdlib.h>
#include "coord_list.h"

void list_add(CoordList* list, int x, int y){
  Coord* coord;
  coord = (Coord*)malloc(sizeof(Coord));
  coord->x = x; coord->y = y;
  coord->next = list->head;
  list->head = coord;
}

void list_clear(CoordList* list){
  Coord *ptr, *tmp;
  ptr = list->head;
  while(ptr){
    tmp = ptr;
    ptr = ptr->next;
    free(tmp);
  }
  list->head = 0x0;
}

Coord* list_del(CoordList* list, int x, int y){
  Coord *prev, *ptr;
  prev = ptr = list->head;
  if(!prev) { return NULL; }
  while(ptr){
    if(ptr->x == x && ptr->y == y){ break; }
    prev = ptr; ptr = ptr->next;
  }
  if(ptr){ prev->next = ptr->next; }
  return ptr;
}

void list_each(CoordList* list, void (*func)(Coord)){
  Coord *ptr;
  ptr = list->head;
  while(ptr){
    func(*ptr);
    ptr = ptr->next;
  }
}

int list_len(CoordList* list){
  int i = 0;
  Coord* ptr;
  ptr = list->head;
  while(ptr){ ptr = ptr->next; i++; }
  return i;
}

Coord* list_take(CoordList* list){
  Coord *prev, *ptr;
  prev = ptr = list->head;
  if(!prev) { return NULL; }
  while(ptr->next){ prev = ptr; ptr = ptr->next; }
  prev->next = NULL;
  return ptr;
}
