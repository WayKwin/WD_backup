#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
pthread_mutex_t mutex;
pthread_cond_t cond;
int flag = 0;

void* product(void* msg)
{
    char* who = (char*) msg;
    pthread_mutex_lock(&mutex);
    flag = 1;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);
    return NULL;
}
void* consume(void* msg)
{
    char* who = (char*) msg;
    pthread_mutex_lock(&mutex);
    while(flag == 0)
        pthread_cond_wait(&cond, &mutex);
    printf(" %s said : i got the flag\n", who);
    flag = 0;
    pthread_mutex_unlock(&mutex);
    return NULL;
}
int main()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_t producter, consumer_1, consumer_2;
    pthread_create(&producter, NULL, product, "producter");
    pthread_create(&consumer_1, NULL, consume, "consumer_1");
    pthread_create(&consumer_2, NULL, consume, "consumer_2");
    pthread_join(producter, NULL);
    pthread_join(consumer_1, NULL);
    pthread_join(consumer_2, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}
