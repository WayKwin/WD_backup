#include<stdio.h>
#include<unistd.h>
#include<signal.h>
void really_void()
{

}
unsigned int mysleep_r(unsigned int sleep_time)
{
    struct sigaction newact, oldact;
    sigset_t newmask,oldmask;

    sigemptyset(&newmask);
    sigemptyset(&oldmask);

    newact.sa_handler = really_void;
    sigaction(SIGALRM, &newact, &oldact);
    //先阻塞alarm信号
    sigaddset(&newmask,SIGALRM);
    sigprocmask(SIG_BLOCK,&newmask,&oldmask);
    sigdelset(&oldmask, SIGALRM);
    //恢复信号
    alarm(sleep_time);

    //在闹钟响起后解除阻塞并且挂起,两个合成一步,原子操作
    //sigsuspend 是在挂起前把block表设置成 参数sigmask 信号集,收到信号错误返回后恢复block表
    sigsuspend(&oldmask);
    //有一种可能,在阻塞闹钟信号前有一个闹钟快被唤醒了.在sigsuspend函数解除阻塞后这个闹钟先响了
    //这里使用sigsuspend只是保证 alarm信号一定会会把sigsuspend唤醒(之前可能会alarm设置好后程序被切换走很久,触发信号后才被puase(),那么puase会一直被挂起)
    unsigned unsleep = alarm(0);
    //结束睡眠 恢复以前的block表 和 处理信号动作
    sigprocmask(SIG_UNBLOCK, &oldmask, NULL);
    sigaction(SIGALRM, &oldact, NULL);
    return unsleep;
}
int  mysleep( int sleep_time )
{
    //bug
    int unsleep;
    struct sigaction act,oldact;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = really_void;
    sigaction(SIGALRM,&act,&oldact);
    int result_member = sigismember(&act.sa_mask,SIGALRM);
    printf("result_member : %d\n",result_member);
    //保证闹钟和挂起是原子操作
    alarm(sleep_time);
    pause();
    //有可能进入函数之前设置了闹钟,而且闹钟比mysleep函数闹钟早响
    //所以用alarm(0)取消后响的闹钟并返回后响的闹钟还有几秒响
    unsleep = alarm(0);
    sigaction(SIGALRM,&oldact,NULL);
    return unsleep;
}
int main()
{
    printf("i will sleep 3 s\n");
    mysleep(3);
    printf("im wake up\n");
    return 0;
}
