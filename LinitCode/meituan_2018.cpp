#include<iostream>
// 121 212 1212 
// 12 122

#include<vector>
#include<string>
#include<deque>
using namespace std;
#include<map>
int main()
{
    int s;
      cin >> s;
        vector<int> vc;
          if (s == 1)
          {
                cout << 1 << endl;
                    return 0;
                      
          }
            if (s == 2)
            {
                  cout << 2 << endl;
                      return 0;
                        
            }
              if (s > 2)
              {
                    int yu = s % 3;
                        int sh = s / 3;
                            while (sh)
                            {
                                    vc.push_back(1);
                                          vc.push_back(2);
                                                --sh;
                                                    
                            }
                                if (yu != 0)
                                {
                                        vc.push_back(yu);
                                            
                                }
                                  
              }
                for (int i = vc.size() - 1; i >= 0; --i)
                {
                      cout << vc[i];
                        
                }
                  cout << endl;
                    return 0;

}
