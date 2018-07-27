
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/tcp.h>
#include<netpacket/packet.h>

#include<string.h>
int main()
{
  int sfd = socket(AF_INET,SOCK_RAW,IPPROTO_UDP);
  if(sfd == -1) perror("socket"),exit(1);
  int op = 1;
  // 抓取数据包,并且捕获IP头部
  setsockopt(sfd,IPPROTO_TP,IP_HDRINCL,&op,sizeof(op));

  char buf[1500] = {};
  while(1)
  {
    memset(buf,0x00,sizeof buf);
    int r = read(sfd,buf, 1500);
    if( r <= 0 )  break;

    struct ip *p_ip = (struct ip*)(buf);
   printf("%s <----------------->", inet_ntoa((p_ip->ip_dst)));
   printf("%s\n",inet_ntoa(p_ip->ip_src));

   struct tcphdr *p_tcp =  (struct tcphdr*)( buf + (p_ip->ip_hl>>2));
   printf("%hu : %hu\n",ntohs(p_tcp->dest), ntohs(p_tcp->source));
         
  }
  return 0;
}

