#include"hash.h"
#include<stdlib.h>
// insert
// 1.判断hash是否能继续插入(根据负载因子判断)
// 2.根据key计算offset
// 3.从offset 位置开始线性往后查找 找到第一个状态为Empty的(下标查找)
// 4. 如果发现key相同,查找失败
// 5++ size;
//
//4
//5
//---------------------------------
//remove 不能将此元素变为 empty, 因为下次在超找时遇到empty会停止(就找不到这个元素
//后面的目标元素了),应该将此元素变为delete状态
size_t GetHashTableCapacity(HashTable* ht)
{
  if(ht  == NULL)
    return -1;
  return ht->capacity;
}
size_t hash_func( KeyType key,HashTable*ht)
{
  return key % GetHashTableCapacity(ht); 
}

void HashInit(HashTable* ht,HashFunc hash_func)
{
  if(ht == NULL || hash_func == NULL)
    return;
  ht->capacity = 1000;
  ht->data= (HashElem*) malloc(sizeof(size_t)* ht->capacity);
  ht->size = 0;
  ht->func = hash_func;
  size_t i = 0;
  for( ; i < ht->size; i++ )
  {
    ht->data[i].state  = Empty;
  }
}
void HasDestory(HashTable* ht)
{
  if(ht == NULL)
    return;
  free(ht->data);
  ht->data = NULL;
  ht->size = 0;
  ht->func = NULL;
  ht->Load_Factor = 0.8;
}
void HashInsert(HashTable* ht,HashElem elem)
{
  KeyType key = elem.key;
  if(ht == NULL)
    return;
  if(ht->size >= ht->capacity * ht->Load_Factor)
  {
    //动态扩容考虑 元素的拷贝
    //TODO
    
  }
  size_t offset = (*ht->func)(key,ht);
  //使用 != empty 局限性,delete 状态 !=empty 但是可以插入
  //是vaild表示被占用
  while(ht->data[offset].state == Vaild  )
  {
    offset++;
    //在占用中找到了重复元素
    if(ht->data[offset].key == key)
    {
      //重复元素
      printf("重复元素\n");
      return;

    }
    if( offset == ht->capacity )
    {
      //有填充因子存在 不会死循环
      offset = 0;
    }
  }


  //找到第一个状态不是 已经占用的位置插入
  ht->data[offset] = elem;     
  ht->data[offset].state = Vaild;
  ht->size++;
}
ValType HashFind(HashTable* ht,  KeyType key)
{
  if(ht == NULL)
    return -1;
  size_t offset = (*hash_func)(key,ht);
  //不为空但是又不是 key offset ++
  while(1)
  {
    //碰到查找的元素是delete状态
    //其实可以忽略,往后找空的就行
    if(ht->data[offset].state == Empty)
    {
      printf("not found \n");
      return -1;
    }
    //排除delete状态
    if(ht->data[offset].key == key && ht->data[offset].state == Vaild ) 
    {
     return ht->data[offset].val; 
    }
    offset++;
    if(offset == ht->capacity)
      offset = 0;
  }
  //排除处于空或者删除状态,剩下while结束条件就是key == key 了(错误)
  //遇到删除的状态还得往后找(删除后面元素的状态可能是vaild)
  //只有遇到空状态才表示查找失败(空表示此位置肯定没有进行插入,它后面的元素就不可能是哈希冲突造成的vaild状态)
}
void  HashRemove(HashTable* ht,  KeyType key)
{
  if(ht == NULL)
    return ;
  size_t offset = (*hash_func)(key, ht);
  while(ht->data[offset].state != Empty)
  {
    if(ht->data[offset].key == key && ht->data[offset].state == Vaild)
    {
      ht->data[offset].state = Deleted;
      return;
    }
    offset++;
    if(offset == ht->capacity)
    {
      offset = 0;
    }
  }
  printf("not found \n");
  return;
}
void HashPrint(HashTable* ht)
{
  if(ht == NULL)
    return;
  size_t i = 0;
  for( ;  i < ht->capacity; i++ )
  {
    if(ht->data[i].state != Vaild)
    {
      continue;
    }
    printf("[%lu|%d|%d] " ,i, ht->data[i].key, ht->data[i].val);
  }
  printf("\n");
}
