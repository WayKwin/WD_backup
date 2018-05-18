#include<iostream>
#include<vector>
using namespace::std;
const char* CanOrder(vector<int>&array,int length)
{
    int  i = 0;
      int anti_flag = 0;
        int  fristAntiNumber ;
          int fristAntiCome = 0;
            for( ; i < length  -1 ; i++  )
            {
                  if(array[i] >array[i + 1] &&  fristAntiCome  ==0)
                  {
                            fristAntiNumber = array[i];
                                  anti_flag = 1;
                                         fristAntiCome = 1;
                                             
                  }
                      else if(array[i] >array[i + 1] )
                      {
                                anti_flag = 1;
                                    
                      }
                         else  if(array[i] < array[ i +1 ]   && anti_flag == 1)
                         {
                                    break;
                                          
                         }
                           
            }
              if(fristAntiCome == 1 &&  fristAntiNumber > array[ i +1 ])
              {
                      return "no";
                           
              }
                for(i += 1; i +1 < length; i++)
                {
                      if(array[i] > array[ i +1 ])
                      {
                                  return "no";
                                         
                      }
                        
                }
                  return "yes";

}
int main()
{
    int length  = 4;
      //cin >> length;
        vector<int> v1 = {3,1,2,4};
            //while(v1.size() != length)
            //{
                  //cin >> v1[i++];
            //}
              cout<< CanOrder(v1,length) ;
                return 0;
}
