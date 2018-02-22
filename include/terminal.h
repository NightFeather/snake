
#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void get_terminal_size(int*, int*);

void puts_at(int,int,char*);

int getch();
int getche();

#endif
