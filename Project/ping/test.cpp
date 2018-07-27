#include<netpacket/packet.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netpacket/packet.h>
#include<net/ethernet.h>
#include<string.h>
//IP在磁盘上写着
// rarp  知道mac  请求ip
// 
int main()
{

  //rarp  知道mac 找到ip
  int sfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  if(sfd == -1);
  char buf[2000];

  while(1)
  {
    memset(buf,0x00,sizeof buf);
    if( read(sfd, buf, sizeof buf) < 0 )
      break;
    struct ethhdr *p_e = (struct ethhdr*)(buf);

    printf("%02x,%02x,%02x,%02x,%02x,%02x< - >",
        p_e->h_source[0],
        p_e->h_source[1],
        p_e->h_source[2],
        p_e->h_source[3],
        p_e->h_source[4],
        p_e->h_source[5]);
    printf("%02x,%02x,%02x,%02x,%02x,%02x\n",
        p_e->h_dest[0],
        p_e->h_dest[1],
        p_e->h_dest[2],
        p_e->h_dest[3],
        p_e->h_dest[4],
        p_e->h_dest[5]);
    if(ntohs(p_e->h_proto) == 0x0800)
    {
      printf("\tip\n");
    }
    if(ntohs(p_e->h_proto) == 0x0806)
    {
      printf("\tarp\t");
    }

  }
  
}
