#pragma once
#include<stdio.h>
#define HashMaxSize 1000
typedef int KeyType;
typedef char ValType;
typedef size_t (*HashFunc)(KeyType key );
//每个hashtable内的状态``
typedef struct HashEelem{
  KeyType key;
  ValType val;
  struct HashEelem* next;
}HashEelem;
typedef struct HashTable{
  // 哈希桶, 每个链表的指针
  HashEelem* data[HashMaxSize];
  size_t size;
  //哈希桶不需要填装因子和状态枚举,也不需要动态
  //size_t capacity;
  //// 填装因子
  HashFunc func;
}HashTable;
size_t hash_func( KeyType key);
// 初始化 每个指针数组为 NULL 
//  size = 0
//  指定hash_func
void HashInit(HashTable* ht,HashFunc hash_func);
//  释放每个链表中的节点 并且将数组每个元素变成NULL
//  size = 0
void HashDestory(HashTable* ht);
//  通过hash_func算出偏移量
//  如果 此地址不为NULl 进行尾插while( cur->next != NULL )
void HashInsert(HashTable* ht,HashEelem elem);
//  hash_fun 算出偏移量
//  链表头结点为空 return NULL
//  在链表中遍历,没有,返回NULL
ValType HashFind(HashTable* ht,  KeyType key);

size_t hash_func( KeyType key);
// hash_func 算出节点
// 然后在链表中删除指定的值
void  HashRemove(HashTable* ht,  KeyType key);
void HashPrint(HashTable* ht);
