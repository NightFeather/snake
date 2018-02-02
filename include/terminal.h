
#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include <sys/ioctl.h>
#include <unistd.h>

typedef struct {
  int row, col;
} termsize;

termsize get_terminal_size();


#endif
