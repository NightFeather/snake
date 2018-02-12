#include <stdlib.h>
#include "coord_list.h"

void list_add(CoordList* list, int x, int y){
  Coord* coord;
  coord = (Coord*)malloc(sizeof(Coord));
  coord->x = x; coord->y = y;
  coord->next = list->head;
  list->head = coord;
}

Coord* list_take(CoordList* list){
  Coord *prev, *ptr;
  prev = ptr = list->head;
  if(!prev) { return NULL; }
  while(ptr->next){ prev = ptr; ptr = ptr->next; }
  prev->next = NULL;
  return ptr;
}
