#include<stdio.h>
#include<curses.h>
#include<unistd.h>
int main()
{
  int i;
  initscr();
  clear();
  for( i = 0; i < LINES; i++ )
  {
    move(i, i + i);
    if( i %2 == 1 )
      standout();
    addstr("Hello , world\n");
    if( i % 2 == 1 )
      standend();
    sleep(1);
    refresh();
  }

  // gerch()才是关键
  getch();
  endwin();
  return 0 ;
}