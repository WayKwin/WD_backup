#include"hash.h"
#include<stdlib.h>
#include<unistd.h>
size_t hash_func( KeyType key)
{
  return key % HashMaxSize; 
}
void HashInit(HashTable* ht,HashFunc hash_func)
{
  if(ht == NULL)
    return;
  int i = 0;
  for( ; i < HashMaxSize; i++ )
  {
    ht->data[i] = NULL;
  }
  ht->size = 0;
  ht->func = hash_func;
}
void HashDestory(HashTable* ht)
{
  if(ht == NULL)
    return;
  size_t i = 0;
  for(; i < HashMaxSize; i++)
  {
    HashEelem* cur = ht->data[i];
    HashEelem* to_delete = NULL;
    while(cur)
    {
      to_delete = cur;
      cur= cur->next;
      free(to_delete);
      to_delete = NULL;
    }
  }
 ht->size = 0; 
}
HashEelem* CreateNode(KeyType key, ValType val)
{
   HashEelem* elem =    (HashEelem*)malloc(sizeof(HashEelem));
   if(elem == NULL)
     return NULL;
   elem->key = key;
   elem->val = val;
   elem->next = NULL;
   return elem;
}
void HashInsert(HashTable* ht,HashEelem elem)
{
  if(ht == NULL)
    return;
  size_t offset = ht->func(elem.key);
  if(ht->data[offset] == NULL)
  {
    ht->data[offset] = CreateNode(elem.key,elem.val);
  }
  else 
  {
    HashEelem* new_node= CreateNode(elem.key,elem.val);
    new_node->next = ht->data[offset];
    ht->data[offset] = new_node;
  }
  ht->size++;
}
ValType HashFind(HashTable* ht,  KeyType key)
{
  if(ht == NULL)
    return -1;
  size_t offset = ht->func(key);
  HashEelem* cur = ht->data[offset];
  while(cur)
  {
   if(cur->key == key)
   {
     return cur->val;
   }
   cur = cur->next;
  }
  printf("not found\n");
  return -1;
}
void  HashRemove(HashTable* ht,  KeyType key)
{
  if(ht == NULL)
    return;
  size_t offset = ht->func(key);
  HashEelem* cur = ht->data[offset];
  HashEelem* pre_cur = NULL;
  while(cur)
  {
    if( cur->key == key )
    {
      break;
    } 
    pre_cur = cur;
    cur = cur->next;
  }
  if(cur == NULL)
  {
    printf("empty key \n");
  }
  else if(pre_cur == NULL)
  {
    free(cur);
    cur = NULL;
  }
  else 
  {
    free(cur);
    cur = NULL;
   pre_cur->next = NULL; 
  }
}
void HashPrint(HashTable* ht)
{
  size_t i = 0;
  for(; i < HashMaxSize; i++)
  {
    if( ht->data[i] == NULL )
      continue;
    HashEelem* cur = ht->data[i] ;
    printf("第%lu条链表结构如下\n",i); 
    while(cur)
    {
      /*sleep(1);*/
      printf("[key: %d| val: %d] ", cur->key,cur->val);
      cur = cur->next;
    }
    printf("\n");
  }
  printf("\n");
}





