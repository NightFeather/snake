
#ifndef __COORD_LIST_H__
#define __COORD_LIST_H__

typedef struct _coord {
  struct _coord* next;
  int x,y;
} Coord;

typedef struct {
  Coord* head;
} CoordList;

void list_add(CoordList*,int,int);
void list_del(CoordList*,int,int);
Coord* list_take(CoordList*);
void list_clear(CoordList*);


#endif
