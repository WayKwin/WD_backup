#pragma once
#include<stdio.h>
#define HashMaxSize 1024
typedef int KeyType;
typedef char ValType;
typedef size_t (*HashFunc)(KeyType key );
//每个hashtable内的状态``
typedef struct HashEelem{
  KeyType key;
  ValType val;
  struct HashEelem* next;
}HashElem;
typedef struct HashTable{
  HashEelem* data[HashMaxSize];
  size_t size;
  //哈希桶不需要填装因子和状态枚举,也不需要动态
  //size_t capacity;
  //// 填装因子
  HashFunc func;
}HashTable;
void HashInit(HashTable* ht,HashFunc hash_func);
void HashDestory(HashTable* ht);
void HashInsert(HashTable* ht,HashEelem elem);
ValType HashFind(HashTable* ht,  KeyType key);
size_t hash_func( KeyType key,HashTable*ht);
void  HashRemove(HashTable* ht,  KeyType key);
void HashPrint(HashTable* ht);
