#include<unistd.h>
#include<stdio.h>
typedef enum state{
  NORMAL,
  FOUND_SLASH,
  CPP_COMMENT,
  C_COMMENT,
  FOUND_START,
}state;
int main()
{
  FILE* input,*output;
  input = fopen("./in.c","r");
  output = fopen("./output.c","w");
  char ch,nextch;
  state s = NORMAL;
  while(1)
  {
   ch = fgetc(input);
   if(ch == EOF)
   {
     break;
   }
    switch(s)
    {
      case NORMAL:
        {
          if(ch == '/')
          {   
            //开始转换
            fputc('/',output);
            s = FOUND_SLASH;
          }
          else 
          {
            fputc(ch,output);
          }
        break;
        }
      case FOUND_SLASH:
        {
          if(ch == '/')
          {
            fputc('/',output);
            s = CPP_COMMENT;
            //c++
          }
          else if( ch == '*' )
          {
            fputc('/',output);
            s = C_COMMENT;
          }
        break;
        }
      case CPP_COMMENT:
        {
          if(ch == '\n')
          {
            //back to normal
            fputc('\n',output);
            s = NORMAL;
          }
          else 
          {
            //c++注释
            fputc(ch, output);
          }
          break;
        }
      case C_COMMENT:
        {
          if(ch == '*')
          {
            s = FOUND_START;
          }
          //多行注释
          else if(ch == '\n')
          {
            fputc('\n',output);
            fprintf(output,"//");
          }
          else 
          {
            fputc(ch,output);
          }
        break;
        }
      case FOUND_START:
        {
          //  /*  */
          //  //
          if(ch  == '/')
          {
            nextch = fgetc(input);
            if(nextch != '\n')
              fputc('\n',output);
           ungetc(nextch,input);
            s = NORMAL;
            //注释结束换行
          }
          /*   *   */
          // *
          else if(ch == '*')
          {
            s = FOUND_START;
            fputc('*',output);
          }
          else  
          {
             /** 5      */
            fputc('*',output);
            fputc(ch,output);
            s = C_COMMENT;
          }
          break;
        }
    }
  }
}


