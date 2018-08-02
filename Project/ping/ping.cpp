//防止隐式包含
//顺序: system-call
//      c-lib 
//      yours
#include<unistd.h>
#include<sys/time.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netinet/ip_icmp.h>
#include<netinet/ip.h>
#include<netdb.h>
#include<string.h>
#include<stdio.h>
#include<signal.h>
#include<math.h>
#include<vector>
#include<algorithm>

#define DATA_LEN 56

int sendnum = 0;//发送数据包编号
int recvnum = 0;//接受数据包的编号
char sendbuf[1024];//发送数据包
char recvbuf[1024]; //接受数据包
char dst[60];
std::vector<float> v;
struct timeval Begin;
//address.dst_address.domain[1] = 0;
//校验和的起始地址
//len是数据大小和字节
unsigned short chksum(unsigned short *addr,int len)
{
#if 1
  // - -
  // - -
  // - -  最后一个 - 没有(奇数个)

  int32_t ret = 0;
  //数据奇数个
  while(len > 1)
  {
    ret += *addr++;
    len -= 2;
  }
  //奇数个 len 为1 要去掉最后一个16位的后八位
  if( len == 1 )
  {
    ret += *(unsigned char*) addr;
  }
  // ret 32位
  ret = ( ret >> 16 ) + (ret & 0xffff);
  //防止溢出
  ret += (ret >> 16);
  return (unsigned short)~ret;
#endif
}
float diff_time(struct timeval *end,struct timeval*begin)
{
  // 秒和微秒都变成 毫秒 进行计算
  float ret = (end->tv_sec - begin->tv_sec) * 1000.0 + (end->tv_usec - begin->tv_usec ) / 1000.0;
  return ret;
}
// num:imcp 报文序号
// pid 组imcp报文的表示字段
void unpack(int num,pid_t pid,struct sockaddr_in from)
{
  struct ip *pip = (struct ip*) recvbuf;
  // 找到ip 数据(即icmp) 注意ip_hl是4倍字节数,所以得*4
  struct timeval end;
  gettimeofday(&end,NULL);
  struct icmp* picmp = (struct icmp*)(recvbuf+(pip->ip_hl << 2) );

  float d = diff_time(&end,(struct timeval*)picmp->icmp_data);
  v.push_back(d);
  printf("%d bytes from %s: imcp_seq=%2d ttl=%2d time=%.4fms\n",
      DATA_LEN + 8,inet_ntoa(from.sin_addr),ntohs(picmp->icmp_seq),pip->ip_ttl,d);
  
}

int pack(int sendnum,pid_t pid)
{
  int len = DATA_LEN + 8;
  struct icmp* picmp  =(struct icmp*)sendbuf;
  //imcp数据的偏移量

  picmp->icmp_type= ICMP_ECHO; 
  // 询问报文 code是0或者8;
  picmp->icmp_code = 8;
  picmp->icmp_id = pid;
  picmp->icmp_seq = htons(sendnum);
  gettimeofday((struct timeval*)(picmp->icmp_data),NULL);

  // 注意校验和一定要放在最后!!!
  picmp->icmp_cksum = chksum((unsigned short*)sendbuf,len);

  return len;

}
// 发送数据
// sfd:套接字
// pid:imcp报头的标识符(进程di)
// addr: 发送目标
void send_packet(int sfd,int pid,struct sockaddr_in* addr)
{
  ++sendnum;
  memset(sendbuf,0x00,sizeof sendbuf);
  int r = pack(sendnum,pid);
  //每次发送数据包 要指定地址,不能用send
  sendto(sfd,sendbuf,r,0,(struct sockaddr*)addr,sizeof(*addr));
}
//hifen.com ping statistics ---
  //8 packets transmitted, 8 received, 0% packet loss, time 7014ms
 // 
 struct  packet_time_data
{
  packet_time_data():max(0),min(0),avg(0),mdev(0){}
    float max; 
    float min; 
    float avg; 
    float mdev; 

};
void handler_signo(int num)
{
  sort(v.begin(),v.end());
  packet_time_data s;
  s.max = *(v.end() -1);
  s.min = *(v.begin());
  for(auto i :v)
  {
    s.avg += i;
  }
  s.avg /= v.size();
  for(auto i : v)
  {
    s.mdev = (i-s.avg) *(i-s.avg);
  }
  s.mdev = sqrtf(s.mdev/v.size());
  char buf[1024];
  int icmp_times = sendnum;
  int received_packets = recvnum;
  float loss_pecent =  1 - recvnum / (sendnum) ;
  struct timeval End;
  gettimeofday(&End,NULL);

  double time =diff_time(&End,&Begin);
  sprintf(buf,"\n--- %s ping statistics ---\n%d packets transmitted, %d received %.1f%% packet loss,time %.fms",dst,icmp_times,received_packets,loss_pecent,time);
  printf("%s\n",buf);
  printf("ret min/avg/max/mdev = %.3f/%.3f/%.3f/%.3fms\n",s.min,s.avg,s.max,s.mdev);

  exit(0);
}
void recv_packet(int sfd,int pid)
{
  memset(recvbuf,0x00,sizeof recvbuf);
  struct sockaddr_in from;
  socklen_t len = sizeof from;
  recvnum++;
  recvfrom(sfd,recvbuf,1024,0,(struct sockaddr*)
            &from,&len);
  //解析数据包
  unpack(recvnum,pid,from);
}
int main(int argc,char* argv[])
{
  if(argc != 2)
  {
    printf("usage: %s ip_address/domain\n",argv[0]);
    exit(1);
  }

  struct sigaction s; 
  s.sa_handler = handler_signo;
  sigaction(SIGINT,&s,NULL);
  struct sockaddr_in addr;
  //?这是什么
  struct hostent* phost;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(argv[1]);
  //如果传入的不是ip地址就可能是域名或者非法输入
  if(addr.sin_addr.s_addr == INADDR_NONE)
  {
    //DNS解析服务
    phost = gethostbyname(argv[1]);
    if(phost == NULL)
      perror("gethostbyname:"), exit(1);
    memcpy((char*)&addr.sin_addr,(char*)phost->h_addr,phost->h_length);
  }
    printf("ping %s(%s) %d bytes of data.\n",argv[1],inet_ntoa(addr.sin_addr),DATA_LEN);
    strcpy(dst,argv[1]);
     
    // 发送imcp报文
    int sfd = socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
    if(sfd == -1)
      perror("socket"),exit(1);
    // 获取当前进程pid
    pid_t pid = getpid();
    gettimeofday(&Begin,NULL);
    while(1)
    {
      // 包装imcp报头 
      send_packet(sfd,pid,&addr);
      recv_packet(sfd,pid);
      sleep(1);
    }
}
