#include<stdio.h>
void fun(int a)
{
    if (a == 3)
        return;
    fun(++a);
    /*fun(a++);*/
    printf("%d\n",a);
}
int main()
{
    int a = 1;
    /*printf("%d, %d ,%d",a++, a++, a++);*/
    //2,3  2
    printf("%d, %d, %d\n", ++a, a + 1, a++);
    /*fun(a);*/
}
