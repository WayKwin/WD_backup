#include<iostream>
using namespace std;

struct ListNode {
    int val;
      struct ListNode *next;
        ListNode(int x) :
          val(x), next(NULL) {
          }
};
// 1, for for 两个循环 找到第一个重合点 o(m+n)
// 2. 栈 ,从栈顶弹出 最后一个相等的 o(min(m,n)) o(max(m,n))
// 3. 先走 长度之差
size_t GetLength(ListNode* link1)
{
  if(link1 == NULL)
    return 0;
  int count = 0;
  while(link1)
  {
    ++count;
    link1 = link1->next;
  }
  return count;
}
ListNode* Linked_commond(ListNode* link1,ListNode* link2)
{
  if(link1 == NULL || link2 == NULL )
    return NULL;
  size_t link1_length = GetLength(link1);
  size_t link2_length = GetLength(link2);
  ListNode* LongLink;
  ListNode* ShortLink ;
  size_t long_length;
  size_t short_length;
  if(link1_length > link2_length)
  {
    LongLink = link1;
    ShortLink =link2;
    long_length = link1_length;
    short_length = link2_length;
  }
  else 
  {
   LongLink = link2;
   ShortLink = link1;
   long_length = link2_length;
   short_length = link1_length;
  }
  size_t Offset =  long_length - short_length;
  while(Offset--)
  {
    LongLink = LongLink->next;
  }
  while(LongLink != ShortLink)
  {
    LongLink = LongLink->next;
    ShortLink = ShortLink->next;
  }
  return LongLink;
}
int main()
{
  
}


