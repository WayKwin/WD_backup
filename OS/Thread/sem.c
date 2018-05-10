#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
pthread_mutex_t mutex;
pthread_cond_t cond_product;
pthread_cond_t cond_consume;
int consumer_step;
int producter_step;
int resource;
int max_storage = 10;
void* create_resource( void* arg )
{
    pthread_mutex_lock(&mutex);
    char * who = (char * ) arg;
    while(1)
    {
        usleep(100000);
        while( producter_step >= consumer_step && resource == max_storage )
        {
            pthread_cond_wait(&cond_product, &mutex);

        }
        resource++;
        producter_step++;
        producter_step %= max_storage;
        // step永远是下一个将要生产或者消费的地方的地方
        printf("%s said : im in %d resource : %d \n",who,producter_step,resource);
        pthread_cond_signal(&cond_consume);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
void* release_resource( void* arg )
{
    pthread_mutex_lock(&mutex);
    char * who = (char * ) arg;
    while(1)
    {
        usleep(600000);
        while( consumer_step >= producter_step && resource == 0 )
        {
            pthread_cond_wait(&cond_consume, &mutex);

        }
        resource--;
        consumer_step++;
        consumer_step %= max_storage;
        printf("%s said : im in %d resource : %d \n",who,consumer_step,resource);
        pthread_cond_signal(&cond_product);
        pthread_mutex_unlock(&mutex);

    }
    return NULL;
}
int main()
{
    consumer_step = 0;
    producter_step = 0;
    resource = 0;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_product, NULL);
    pthread_cond_init(&cond_consume, NULL);
    pthread_t producer, consumer;
    pthread_create(&producer, NULL, create_resource, "producer" );
    pthread_create(&consumer, NULL, release_resource, "consumer" );
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);
}

