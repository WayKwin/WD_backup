#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
volatile int tickets = 1000;

void* sell_tickets(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        if(tickets <=  0)
        {
            printf("sell out\n");
            pthread_mutex_unlock(&mutex);
            break;
        }
        char* id = (char*) arg;
        usleep(1000);
        tickets--;
        printf("%s sells one ticket ,left %d ticket\n", id, tickets);
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t thread1,thread2, thread3;
    pthread_create(&thread1, NULL, sell_tickets, "thread1");
    pthread_create(&thread2, NULL, sell_tickets, "thread2");
    pthread_create(&thread3, NULL, sell_tickets, "thread3");
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
    return 0;
}
