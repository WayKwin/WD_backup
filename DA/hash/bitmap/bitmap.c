#include"bitmap.h"
#include<malloc.h>
#include<string.h>
uint64_t GetSize(uint64_t index)
{
  //总共需要的bit位除以 一个类型占的字节*8 (bit位) + 1
  // 100   100/64 + 1
  uint64_t size = index /( sizeof(BitmapType) * 8 ) + 1;
  return size;
}
uint64_t GetOffset(uint64_t index)
{
  uint64_t size = index %( sizeof(BitmapType) * 8 ) + 1;
  return size;
  
}
void BitmapInit(Bitmap* b, size_t  capacity)
{
  if(b == NULL)
    return;
  b->size = GetSize(capacity); 
  b->data = (BitmapType*) malloc(sizeof(BitmapType) * b->size);
  b->capacity = capacity;
  memset(b->data,0,sizeof(BitmapType) * b->size); 
}
void Bitmapdestroy(Bitmap* b)
{
  if( b == NULL )
    return;
  b->size = 0;
  free(b->data);
  b->data = NULL;
}
int BitmapTest(Bitmap* bm, uint64_t index)
{
  if(bm == NULL || index >= bm->capacity)
    return -1;
  // n  < size
  uint64_t n = GetSize(index);
  //offset 64位
  uint64_t offset =  GetOffset(index) ;
  //注意offset可能移动64位
  uint64_t ret = bm->data[n] & (0x1lu << offset );
  return ret ;
}
void BitmapSet(Bitmap* bm, uint64_t index)
{
  if(bm == NULL || index >= bm->capacity)
    return;
  uint64_t size = GetSize(index);
  uint64_t offset = GetOffset(index);
  bm->data[size] |= (0x1lu << offset);
}
void BitmapUnset(Bitmap* bm, uint64_t index)
{
  if(bm == NULL || index >= bm->capacity)
    return;
  uint64_t size = GetSize(index);
  uint64_t offset = GetOffset(index);
  bm->data[size] &= ~(0x1lu << offset);
}
void BitmapFill(Bitmap* bm)
{
 
}

