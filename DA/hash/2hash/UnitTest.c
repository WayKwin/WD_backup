#include"hash.h"
#include<stddef.h>
#define HEAD \
    do{  \
     printf("\n----------------%s----------------\n",__FUNCTION__); \
    }while(0)

/*void testHashInsert()*/
/*{*/
  /*HEAD;*/
  /*HashTable ht;*/
  /*HashInit(&ht,hash_func);*/
  /*HashEelem elem1;*/
  /*HashEelem elem2;*/
  /*HashEelem elem3;*/
  /*HashEelem elem4;*/
  /*elem1.key  = 1;*/
  /*elem2.key  = 2;*/
  /*elem3.key  = 1001;*/
  /*elem4.key  = 1002;*/
  
  /*elem1.val  = 1;*/
  /*elem2.val  = 2;*/
  /*elem3.val  = 3;*/
  /*elem4.val  = 4;*/
  /*HashInsert(&ht,elem1);*/
  /*HashInsert(&ht,elem2);*/
  /*HashInsert(&ht,elem3);*/
  /*HashInsert(&ht,elem4);*/
  /*HashPrint(&ht);*/
/*}*/
void testFindAndDelete()
{
  HEAD;
  HashTable ht;
  HashInit(&ht,hash_func);
  HashEelem elem1;
  HashEelem elem2;
  HashEelem elem3;
  HashEelem elem4;
  elem1.key  = 1;
  elem2.key  = 2;
  elem3.key  = 1001;
  elem4.key  = 1002;
  
  elem1.val  = 1;
  elem2.val  = 2;
  elem3.val  = 3;
  elem4.val  = 4;
  HashInsert(&ht,elem1);
  HashInsert(&ht,elem2);
  HashInsert(&ht,elem3);
  HashInsert(&ht,elem4);
  printf("插入情况 \n");
  HashPrint(&ht);
  printf("查找测试\n");
  ValType ret = HashFind(&ht,1001);  
  printf("except:3 actul : %d\n",ret);
  printf("删除测试\n"); 
  HashRemove(&ht,2);
  ret = HashFind(&ht,1002);  
  printf("except:4 actul : %d\n",ret);
  ret = HashFind(&ht,2);  
  printf("except:-1 actul : %d\n",ret);
  printf("HashPrint \n");
  printf("except\n");
  printf("[1|1|1] [1|1001|3] [2|1002|4]\n");
  printf("actual: \n");
  HashPrint(&ht);
  HashInsert(&ht, elem2);
  printf("except\n");
  printf("[1|1|1] [2|2|2] [1|1001|3] [2|1002|4]\n");
  printf("actual: \n");
  HashPrint(&ht);
}
int main()
{
  /*testHashInsert();*/
  testFindAndDelete();

}
