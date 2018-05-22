#include"Controller.h"
#include"Model.h"
#include"view.h"
#include<stdlib.h>
#include<assert.h>
#include<unistd.h>
#define bool int
#define true 1
#define false 0
//蛇的初始化
static void _SnakeInitialize(Snake *pSnake)
{
  int i;
  int initLength = 3;
  //初始位置
  int x = 5;
  int y = 5;
  pSnake->pHead = NULL;
  for(i = 0; i < initLength; i++)
  {
    Node* pNode = (Node*) malloc(sizeof(Node));
    pNode->position.x = x+i;
    pNode->position.y = y;
    pNode->pNext = pSnake->pHead;
    pSnake->pHead = pNode;
  }
}
static bool _IsOverLapSnake(int x,int y, const Snake* pSnake)
{
  assert(pSnake != NULL);
  Node* pNode = pSnake->pHead;
  while(pNode)
  {
    if(pNode->position.x == x && pNode->position.y == y)
    {
      return true;
    }
    pNode = pNode->pNext;
  }
    return false;
}
static void _GenerateFood(Position *pPosition, int width, int height, const Snake *pSnake)
{
  int x ;
  int y ;
  do{
  x = rand() % width;
  y = rand() % height;
  }while(_IsOverLapSnake(x , y, pSnake));
  pPosition->x = x;
  pPosition->y = y;
}
static Position _GetNextPosition(const Snake* pSnake)
{
  assert(pSnake != NULL);
  int x, y;

  x = pSnake->pHead->position.x;
  y = pSnake->pHead->position.y;

  switch (pSnake->direction)
  {
    case UP:
       y -= 1;
       break;
    case DOWN:
       y += 1;
       break;
    case LEFT:
       x -= 1;
       break;
    case RIGHT:
       x += 1;
       break;
  };
  Position  p;
  p.x = x;
  p.y = y;
  return p;
}
static bool _IsEatFood(Position* foodPositon, Position* nextPosition)
{
  return (foodPositon->x == nextPosition->x && foodPositon->y == nextPosition->y);
}
static bool _IsKilledByWall(Position* nextPosition,int width,int height)
{
  if(nextPosition->x < 0 || nextPosition->y < 0)
  {
    return true;
  }
  if( nextPosition->x >= width || nextPosition->y >= height )
  {
    return true;
  }
  return false;
}
void GameInitialize(Game *pGame)
{
    assert(pGame != NULL);
      pGame->gameZoneWidth = 16;
        pGame->gameZoneHeight = 14;
          pGame->score = 0;
            pGame->scorePerFood = 10;
              pGame->interval = 300;

                _SnakeInitialize(&pGame->snake);
                  _GenerateFood(&pGame->foodPostion, pGame->gameZoneWidth, pGame->gameZoneHeight,
                          &pGame->snake);

}

static void _Pause()
{
  //信号处理暂停
}
static bool _IsKilledBySelf(Position nextPosition, const Snake* pSnake)
{
  assert(pSnake == NULL);
  //应该判断下一个节点是否和 身子节点相与
  Node* cur = pSnake->pHead->pNext;
  while(cur)
  {
    if(cur->position.x == nextPosition.x && cur->position.y == nextPosition.y)
    {
      return true;
    }
    cur = cur->pNext;
  }
  return false;
}
static void _DisplaySnake(const UI *pUI, const Snake* pSnake)
{
  Node* pNode = pSnake->pHead;
  while(pNode)
  {
    UIDisplaySnakeBlockAtXY(pUI, pNode->position.x, pNode->position.y);
  }
}
static void _AddHeadAndDisplay(const UI * pUI, Position NextPostion, Snake* pSnake)
{
  Node* new_head = (Node*)malloc(sizeof(Node));
  new_head->position.x = NextPostion.x; 
  new_head->position.y = NextPostion.y; 
  UIDisplaySnakeBlockAtXY(pUI, NextPostion.x,NextPostion.y);
  new_head->pNext = pSnake->pHead;
  pSnake->pHead = new_head;
}
static void _RemoveTailAndDisplay(const UI* pUI, Snake* pSnake)
{
  Node* pos = pSnake->pHead;
  //蛇的长度不会减少到3个一下,
  while(pos->pNext->pNext)
  {
   pos = pos->pNext; 
  }
  UICleanBlockAtXY(pUI, pos->pNext->position.x,pos->pNext->position.y);
  free(pos->pNext);
  pos->pNext = NULL;
}
void GameRun(Game* pGame)
{
  UI ui;
  UIInitialize(&ui, pGame->gameZoneWidth, pGame->gameZoneHeight);
  UIDisplayWizard(&ui);


  UIDisplayGameZone(&ui);
  //展示食物

  UIDisplayFoodBlockAtXY(&ui, pGame->foodPostion.x, pGame->foodPostion.y);
  _DisplaySnake(&ui, &pGame->snake);
  while(1)
  {
    // switch 按键终端
    switch(1)
    {
      
    }
  
  Position NextPosition = _GetNextPosition(&pGame->snake);
  if(_IsEatFood(&pGame->foodPostion,&NextPosition))
  {
     _AddHeadAndDisplay(&ui, NextPosition, &pGame->snake);
     _GenerateFood(&pGame->foodPostion, pGame->gameZoneWidth, pGame->gameZoneHeight, &pGame->snake);
     UIDisplayFoodBlockAtXY(&ui, pGame->foodPostion.x, pGame->foodPostion.y);
     pGame->score += pGame->scorePerFood;
  }
  else 
  {
     _AddHeadAndDisplay(&ui, NextPosition, &pGame->snake);
     _RemoveTailAndDisplay(&ui,&pGame->snake);
  }
  if (_IsKilledByWall(&NextPosition, pGame->gameZoneWidth, pGame->gameZoneHeight))
  {
          break;
  }

  if (_IsKilledBySelf(NextPosition, &pGame->snake))
  {
          break;
  }
    sleep(pGame->interval);
}
}
