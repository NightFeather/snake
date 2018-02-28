
#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#define BORDER_TOP    (unsigned char)(0b1000)
#define BORDER_BOTTOM (unsigned char)(0b0100)
#define BORDER_LEFT   (unsigned char)(0b0010)
#define BORDER_RIGHT  (unsigned char)(0b0001)

typedef struct _pane{
  int x, y, width, height, xspan, yspan;
  unsigned char border;
  struct _pane *parent;
} Pane;

Pane* make_pane(int,int,int,int);
Pane* make_subpane(Pane*,int,int,int,int);
void delete_pane(Pane*);

int pane_set_border(Pane*, unsigned char);

int pane_draw_at(Pane*, int, int);

int pane_render(Pane*);

#endif
