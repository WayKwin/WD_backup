#include<iostream>
void Swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
int main()
{
    int a = 10;
    int& b = a;

    //int* c = a;
    //int b = 20;
    //const double& c = a;
    ////k
    //Swap(a,b);
        //std::cout << a << std::endl<< b<< std::endl;
}
