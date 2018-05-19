//开发地址发
#pragma once
#include<stdio.h>
typedef int KeyType;
typedef char ValType;
//这个结构体表示哈希表中的一个元素
//这个元素中同时包含了键值对

//判断状态时   使用 !=  可以归类一类状态(方便以后扩充) 不一定 还要调试
//             使用 =  可能在新增状态发生错误
typedef enum State
{
  
  Empty, //空状态
  Vaild,//有效状态
  Deleted,//服务于remove
}State;
struct HashTable;
typedef size_t (*HashFunc)(KeyType key,struct HashTable* );
//每个hashtable内的状态``
typedef struct HashElem{
  KeyType key;
  ValType val;
  State state;
}HashElem;
//[0,size) 不能看作线性的,不能表示哈希表的区间
typedef struct HashTable{
  HashElem* data;
  size_t size;
  size_t capacity;
  // 填装因子
  float Load_Factor;
  HashFunc func;
}HashTable;
void HashInit(HashTable* ht,HashFunc hash_func);
void HashDestory(HashTable* ht);
void HashInsert(HashTable* ht,HashElem elem);
ValType HashFind(HashTable* ht,  KeyType key);
size_t hash_func( KeyType key,HashTable*ht);
void  HashRemove(HashTable* ht,  KeyType key);
void HashPrint(HashTable* ht);


