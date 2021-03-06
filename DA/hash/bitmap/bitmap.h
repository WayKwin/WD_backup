#include<stdio.h>
#include<stdint.h>
typedef uint64_t BitmapType;
typedef struct Bitmap
{
  BitmapType* data;
  size_t capacity;
  uint64_t size;
}Bitmap;
// size = capacity/( (data[0]) *8 ) + 1
 // capacity = 所需容量
 // size(所需字节数) = 所需容量/ ( 类型所占字节数 * 8 ) + 1  
 // 
 //  1. 计算size
 //  2. malloc  size
void BitmapInit(Bitmap* b, size_t  capacity);
void Bitmapdestroy(Bitmap* b);
// 0x1ul
//  
int BitmapTest(Bitmap* bm, uint64_t index);
void BitmapSet(Bitmap* bm, uint64_t index);
void BitmapUnset(Bitmap* bm, uint64_t index);
void BitmapFill(Bitmap* bm);
void Bitmapclever(Bitmap* bm);




