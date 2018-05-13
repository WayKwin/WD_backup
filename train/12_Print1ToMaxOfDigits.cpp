#include<stdio.h>
#include<string.h>
bool Increament(char* number)
{
  bool isOverflow = false;
  int nTakeOver = 0;
  int nLength = strlen(number);
  for(int i = nLength - 1; i >= 0; i--)
  {
    int nSum = number[i] - '0' + nTakeOver;
    if( i == nLength - 1 )
      nSum++;
    if(nSum >= 10)
    {
      if( i == 0 )
        isOverflow = true;
      else 
      {
        nSum -= 10;
        nTakeOver = 1;
        number[i] = '0' + nSum;
      }
    }
    else  
    {
      number[i] = '0' + nSum;
      break;
    }
    }
  return isOverflow;
 }

void PrintNumber(char* number)
{
  bool isBeginning0 = true;
  int nLength = strlen(number);
  for( int i = 0; i < nLength; ++ i )
  {
    if( isBeginning0 && number[i] != '0' )
      isBeginning0 = false;
    if(!isBeginning0)
    {
      printf("%c",number[i]);
    }
  }
  printf("\t");
}
void Print1ToMaxOfDigits(int n )
{
  if( n <= 0 )
    return;
  char* number = new char [n + 1];
  memset(number, 0, n);
  number[n] = '\0';
  // 通过溢出来判断是否打完
  while(!Increament(number))
  {
    // 打印数字 记得忽略前面的0
    PrintNumber(number);
  }
}
int main()
{
  Print1ToMaxOfDigits(2);
  return 0;
}
