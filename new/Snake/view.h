#pragma once
#include<stdio.h>
#include<assert.h>
typedef struct UI
{
  //字符个数
  int gameZoneWidth;
  int gameZoneHeight;

  // 边缘 Margin 光标宽度
  int marginTop;
  int marginLeft;

  char* snakeBlock;
  char* foodBlock;
  char* wallBlock;
  int blockWidth;
  
}UI;

void UIInitialize(UI *pUI, int gameZoneWidth, int gameZoneHeight);

void UIDisplayFoodBlockAtXY(const UI *pUI, int x, int y);

void UICleanBlockAtXY(const UI *pUI, int x, int y);

void UIDisplaySnakeBlockAtXY(const UI *pUI, int x, int y);

void UIDestroy(UI *pUI);

void UIDisplayWizard(const UI *pUI);

void UIDisplayGameZone(const UI *pUI);
