#include<iostream>  
#include<vector>  
#include<cstring>  
using namespace std;  
#include<assert.h>  
  
void Combination(char *str ,int number,vector<char> &result);  
  
void Combination(char *str)  
{  
    assert(str != NULL);  
    vector<char> result;  
    int i , length = strlen(str);  
    for(i = 1 ; i <= length ; ++i)  
        Combination(str , i ,result);  
}  
  
void Combination(char *str ,int number , vector<char> &result)  
{  
    assert(str != NULL);  
    if(number == 0)  
    {  
            static int num = 1;  
            printf("第%d个组合\t",num++);  
      
            vector<char>::iterator iter = result.begin();  
            for( ; iter != result.end() ; ++iter )  
                printf("%c",*iter);  
            printf("\n");  
            return ;  
        }  
    if(*str == '\0')  
        return ;  
    //有str的组合
    result.push_back(*str);  
    Combination(str + 1 , number - 1 , result);  
    // 没有 *str 的组合
    result.pop_back();  
    Combination(str + 1 , number , result);  
}  
  
int main(void)  
{  
    char str[] = "abcd";  
    Combination(str);  
    return 0;  
}  
