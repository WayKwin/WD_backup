#include "hash_func.h"
#include"boolmFilter.h"
void BloomFilterInit(BloomFilter* bf,uint64_t capacity)
{
  BitmapInit(&bf->bm, capacity);
  bf->bool_hash[0] = BKDRHash;
  bf->bool_hash[1] = SDBMHash;
}
void BloomFilterDestroy(BloomFilter* bf)
{
  Bitmapdestroy(&bf->bm);
}
void BloomFilterInsert(BloomFilter* bf,const char* str)
{
  if(bf == NULL || str == NULL)
    return;
  size_t  hash1= bf->bool_hash[0](str);
  size_t index_1 = hash1 % bf->bm.capacity; 
  size_t hash2= bf->bool_hash[0](str);
  size_t index_2 = hash2 % bf->bm.capacity; 
  BitmapSet(&bf->bm,index_1);
  BitmapSet(&bf->bm,index_2);
}
void BloomFilterSearch( BloomFilter* bf,const char* str)
{
  if(bf == NULL || str == NULL)
    return;
  size_t  hash1= bf->bool_hash[0](str);
  size_t index_1 = hash1 % bf->bm.capacity; 
  size_t hash2= bf->bool_hash[0](str);
  size_t index_2 = hash2 % bf->bm.capacity; 
  int ret1 = BitmapTest(&bf->bm,index_1);
  int ret2 = BitmapTest(&bf->bm,index_2);
  if(ret1 &&ret2)
  {
    printf("该字符串在布隆过滤器中\n");
  }
  else 
    printf("该字符串不在布隆过滤器中\n");
}
void testBloomFilter()
{
  BloomFilter bf;
  BloomFilterInit(&bf,1000);
  BloomFilterSearch(&bf,"aaa");
  BloomFilterInsert(&bf,"aaa");
  BloomFilterSearch(&bf,"aaa");
   
}
int main()
{
  testBloomFilter(); 
}


