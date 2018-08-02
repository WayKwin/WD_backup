#include<stdio.h>
int main(int argc,char* argv[])
{
	int* a[100];
	printf("%d\n",sizeof(a));
	printf("%d\n",sizeof(argv));
	printf("%d\n",sizeof(argv[1]));
}

