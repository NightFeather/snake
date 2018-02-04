
#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int row, col;
} termsize;

termsize get_terminal_size();

void puts_at(int,int,char*, int);

#endif
