#include"../log.h"
#include<iostream>
int main()
{
   LogInfo("open");

   Logger::GetInstance().process();

}

