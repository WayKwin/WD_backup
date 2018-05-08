#include<stdio.h>
#include<string.h>
void SortAge(int ages[], int length)
{
    if( ages == NULL || length <=0  )
    {
        printf("invalid input \n");
        return;
    }
    const int OldestAge = 70;
    int TimesOfAge[OldestAge + 1];
    memset(TimesOfAge, 0,sizeof(TimesOfAge));
    int i = 0;
    for( ; i < length; i ++  )
    {
        if(ages[i] <  18 || ages[i] > OldestAge)
        {
            printf("wrong age, postion : %d \n", i);
            continue;
        }
        ++TimesOfAge[ages[i]];
    }
    int j = 0;
    int index = 0;
    for( i = 18; i < OldestAge; i++ )
    {
        for( j = 0; j  <TimesOfAge[i]; j ++  )
        {
            //OldestAge[i]是出现的次数
            /*ages[index] = OldestAge[i];*/
            ages[index] = i;
            index++;
        }
    }
}
