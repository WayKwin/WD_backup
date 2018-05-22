#include "view.h"
#include"Controller.h"
#include<curses.h>
void UIInitialize(UI *pUI, int gameZoneWidth, int gameZoneHeight)
{

  initscr();
  cbreak();
  box(stdscr, ACS_VLINE, ACS_HLINE); 
  nonl();
  noecho();
  curs_set(0);
  pUI->gameZoneWidth = gameZoneWidth;
  pUI->gameZoneHeight = gameZoneHeight;
  pUI->marginTop = 2;
  pUI->marginLeft = 3;
  pUI->snakeBlock = "*";
  pUI->foodBlock = "@";
  pUI->wallBlock = "+";
  pUI->blockWidth = 1;
}
void UIDisplayFoodBlockAtXY(const UI *pUI, int x, int y)
{
  assert(pUI != NULL);
  //直接打印字符串
  mvaddstr(x, y, pUI->foodBlock) ;
  refresh();
}
void UICleanBlockAtXY(const UI *pUI, int x, int y)
{
  assert(pUI != NULL);
  mvaddstr(x, y, " ") ;
  refresh();
}
void UIDisplaySnakeBlockAtXY(const UI *pUI, int x, int y)
{
  assert(pUI != NULL);
  //直接打印字符串
  mvaddstr(x, y, pUI->snakeBlock) ;
  refresh();
  
}
void UIDestroy(UI *pUI)
{
  pUI = NULL;
  endwin();
}
void UIDisplayWizard(const UI *pUI)
{
      mvaddstr(1, 2, "Game: snake    version: 1.0    date: 2011/08/22");  
      mvaddstr(2, 2, "Author: Dream Fly   Blog: blog.csdn.net/jjzhoujun2010");  
      mvaddstr(3, 2, "Usage: Press 'f' to speed up, 's' to speed down,'q' to quit.");  
      mvaddstr(4, 2, "       Nagivation key controls snake moving.");  
      mvaddstr(LINES/2, COLS/2, " welcome to the game");  
      getch();
      refresh();
}
void UIDisplayGameZone(const UI *pUI)
{

}
int main()
{

  Game pGame;
  GameInitialize(&pGame);
  GameRun(&pGame);
  getch();
  /*return 0 ;*/
}
