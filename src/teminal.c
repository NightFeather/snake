#include <termios.h>
#include "terminal.h"

/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

/* reads from keypress, echoes */
int getche(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

void get_terminal_size(int* cols, int* rows){
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  *rows = w.ws_row;
  *cols = w.ws_col;
}

void puts_at(int x, int y, char* string){
  char *ptr = string;
  x *= 2;
  printf("\e[s\e[%d;%dH", row, col);
  while(*ptr != 0){
    putchar(*ptr);
    ptr++; x++;
    if(*ptr > 0x80){
      while((*(ptr++) & 0xc0) == 0x80){ putchar(*ptr);}
      printf("\e[%d;%dH", row, ++col);
    }
  }
  printf("\e[u");
}
