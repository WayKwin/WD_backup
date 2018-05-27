#include"bitmap.h"
void testSet()
{
  Bitmap bitmap;
  printf("set test \n ");
  BitmapInit(&bitmap,1000);
  BitmapSet(&bitmap,456);
  int ret  = BitmapTest(&bitmap,456); 
  printf("except: 1 actul : %d\n",ret);
  BitmapUnset(&bitmap,456);
  ret  = BitmapTest(&bitmap,456); 
  printf("except: 0 actul : %d\n",ret);
  BitmapSet(&bitmap,222);
  ret  = BitmapTest(&bitmap,222); 
  printf("except: 1 actul : %d\n",ret);
  BitmapUnset(&bitmap,222);
  ret  = BitmapTest(&bitmap,222); 
  printf("except: 0 actul : %d\n",ret);

  printf("fill test \n");
  BitmapFill(&bitmap);
  ret  = BitmapTest(&bitmap,0); 
  printf("except: 1 actul : %d\n",ret);

  ret  = BitmapTest(&bitmap,1); 
  printf("except: 1 actul : %d\n",ret);

  ret  = BitmapTest(&bitmap,999); 
  printf("except: 1 actul : %d\n",ret);

  printf("clever test \n");
  Bitmapclever(&bitmap);
  ret  = BitmapTest(&bitmap,0); 
  printf("except: 0 actul : %d\n",ret);
  ret  = BitmapTest(&bitmap,500); 
  printf("except: 0 actul : %d\n",ret);
  ret  = BitmapTest(&bitmap,999); 
  printf("except: 0 actul : %d\n",ret);
  
}
int main()
{
  testSet();
}

