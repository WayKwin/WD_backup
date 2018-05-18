#include"hash.h"
#include<stddef.h>
#define HEAD \
    do{  \
     printf("\n----------------%s----------------\n",__FUNCTION__); \
    }while(0)

void testHashInsert()
{
  HEAD;
  HashTable ht;
  HashInit(&ht,hash_func);
  HashElem elem1;
  HashElem elem2;
  HashElem elem3;
  HashElem elem4;
  elem1.key  = 1;
  elem2.key  = 2;
  elem3.key  = 1001;
  elem3.key  = 1002;
  
  elem1.val  = 1;
  elem2.val  = 2;
  elem3.val  = 3;
  elem4.val  = 4;
  HashInsert(&ht,elem1);
  HashInsert(&ht,elem2);
  HashInsert(&ht,elem3);
  HashInsert(&ht,elem4);
  HashPrint(&ht);
}
int main()
{
  testHashInsert();
}
