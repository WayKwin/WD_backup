#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/tcp.h>
#include<netpacket/packet.h>
#include<netdb.h>
#include<string.h>
#include <linux/if_ether.h>

int main(void)
{
  
  struct hostent *p = gethostbyname("www.baidu.com");
  printf("%s\n", inet_ntoa(*(struct in_addr*)(p->h_addr)));
  return 0;
}

