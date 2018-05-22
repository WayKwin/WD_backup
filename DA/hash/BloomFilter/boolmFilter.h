#pragma  once
#include"../bitmap/bitmap.h"
typedef uint64_t (*BloomHash)(const char*);
#define BloomHashCount 2
//只能查找,插入,不能删除
typedef struct BloomFilter
{
  Bitmap bm;
  //两个函数指针
  BloomHash bool_hash[BloomHashCount];
}BloomFilter;
void BloomFilterInit(BloomFilter* bf,uint64_t capacity);
void BloomFilterDestroy(BloomFilter* bf);
void BloomFilterSearch(BloomFilter* bf,const char* str);
void BloomFilterInsert(BloomFilter* bf,const char* str);
