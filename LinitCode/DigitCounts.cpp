#include<iostream>
using namespace::std;
int digitCounts(int k, int n )
{
    int i =0;
    int j = i;
    int count = 0;
    if ( k == 0 )
        count++;
    for(; i <=n ; i ++ )
    {
        j = i;
        while( j != 0)
        {
            if( j%10 == k )
                count++;
            j /= 10;
        }
    }
    return count;
}
int main()
{
    int ret = digitCounts(1,12);
    cout << ret << endl;
}
