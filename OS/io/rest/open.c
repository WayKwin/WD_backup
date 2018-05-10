#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main()
{
    /*const char* info1 = "Hi,write";*/
    /*const char* info2 = "hi,printf";*/
    /*const char* info3 = "hi,im fwrite";*/
    /*write(1,info1,strlen(info1));*/
    /*printf("%s",info2);*/
    /*fwrite(info3,strlen(info3),1,stdout);*/
    close(1);
    int fd = open("srcfile",O_RDONLY);
    printf("talking to the moon");
    fflush(stdout);
    close(fd);
    /*int fd = 0;*/
    /*if (fd < 0)*/
        /*return -1;*/
    /*char buf[1024];*/
    /*ssize_t n;*/
    /*while((n = read(fd,buf,sizeof(buf)-1)))*/
    /*{*/
        /*if(n > 0)*/
        /*{*/
            /*buf[n] = '\0';*/
            /*write(1,buf,n);*/
        /*}*/
    /*}*/
    return 0;
}
