#include<stdio.h>
#include<malloc.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#define max_size

typedef struct _node
{
    int data;
    struct _node* next;
}node;
typedef struct _stack
{
    node* head;
}stack;
node* create_node(int val)
{
    node * ret = (node*)malloc(sizeof(node));
    ret->data = val;
    ret->next = NULL;
    return ret;
}
void stack_inint(stack *s)
{
    s->head =create_node(0);
}
void stack_push(stack *s, int val)
{
    node* new = create_node(val);
    // 0
    // 10
    // 210
    new->next = s->head;
    s->head = new;
    // 0
    // 01
    // 021
    /*new->next = s->head->next;*/
    /*s->head->next = new;*/
}
void stack_pop(stack*s)
{
    if(s == NULL)
        return;
    if(s->head == NULL )
        return;
    node* to_delete = s->head;
    s->head = s->head->next;
    free(to_delete);
    to_delete = NULL;
}
int  stack_isEmpty(stack*s)
{
    if(s == NULL)
        return 1;
    if(s->head == NULL)
        return 1;
    return 0;
}
node* stack_top(stack* s)
{
    if(s == NULL)
        return NULL;
    if(s->head == NULL)
        return NULL;
    return s->head;
}
void stack_destory(stack* s)
{
    while(stack_isEmpty(s))
    {
        node* to_delete = s->head;
        s->head = s->head->next;
        free(to_delete);
        to_delete = NULL;
    }
}


stack demo_stack;
pthread_mutex_t product_mutex;
pthread_mutex_t consumer_mutex;
pthread_mutex_t product_consume_mutex;
pthread_cond_t can_consume;
pthread_cond_t can_product;
void* thread_product(void* arg)
{
    char* who = (char*)arg;
    while(1)
    {

        /*sleep(3);*/
        sleep(1);
        pthread_mutex_lock(&product_mutex);
        pthread_mutex_lock(&product_consume_mutex);
        printf("==============================\n");
        while(!stack_isEmpty(&demo_stack))
        {
            printf("%s said: there still left one product ,i wait\n",who);
            pthread_cond_wait(&can_product, &product_consume_mutex);
        }
        int i = rand()%100 + 1;
        printf("%s product %d\n",who,i);
        stack_push(&demo_stack,i);
        pthread_cond_signal(&can_consume);
        /*printf("%s said : send can_consume_signal,then wait can_product signal\n");*/
        /*printf("%s said:  wait can_product signal successfully\n");*/
        pthread_mutex_unlock(&product_consume_mutex);
        pthread_mutex_unlock(&product_mutex);
    }
            /*(22,31)*/
            /*rand()%8+23*/

}
void* thread_consume(void* arg)
{
    int i;
    char* who = (char *) arg;
    while(1)
    {
        sleep(1);
        pthread_mutex_lock(&consumer_mutex);
        pthread_mutex_lock(&product_consume_mutex);
        while(stack_isEmpty(&demo_stack))
        {
            //cond 必须加锁,如果你刚准备wait(还没wait) 那边恰好发出一个singal信号之后,你刚进入wait状态,那wait就没有意义了
            //注意如果不释放锁,那么其他线程都会一直等待
            //因为cond unlock后被唤醒第一件事是恢复加锁
            printf("%s said: dont have any product,i wait\n",who);
            pthread_cond_wait(&can_consume,&product_consume_mutex);
        }
        i = stack_top(&demo_stack)->data;
        stack_pop(&demo_stack);
        printf("%s comsume %d\n",who,i);
        pthread_cond_signal(&can_product);
        pthread_mutex_unlock(&product_consume_mutex);
        pthread_mutex_unlock(&consumer_mutex);
    }

}
int main()
{
    pthread_mutex_init(&product_mutex,NULL);
    pthread_mutex_init(&consumer_mutex,NULL);
    pthread_mutex_init(&product_consume_mutex,NULL);
    pthread_cond_init(&can_product,NULL);
    pthread_cond_init(&can_consume,NULL);
    pthread_t producter_1, producter_2, producter_3, consumer_1, consumer_2, consumer_3;
    pthread_create(&producter_1, NULL, thread_product, "producter_1" );
    pthread_create(&producter_2, NULL, thread_product, "producter_2" );
    pthread_create(&producter_3, NULL, thread_product, "producter_3" );
    pthread_create(&consumer_1, NULL, thread_consume, "consumer_1");
    pthread_create(&consumer_2, NULL, thread_consume, "consumer_2");
    pthread_create(&consumer_3, NULL, thread_consume, "consumer_3");
    pthread_join(producter_1, NULL);
    pthread_join(producter_2, NULL);
    pthread_join(producter_3, NULL);
    pthread_join(consumer_1, NULL);
    pthread_join(consumer_2, NULL);
    pthread_join(consumer_3, NULL);

}
/*int main()*/
/*{*/
    /*stack_inint(&demo_stack);*/
    /*int i = 1;*/
    /*for(; i < 6; i++)*/
    /*{*/

        /*node* s;*/
        /*s = demo_stack.head;*/
        /*while(s != NULL)*/
        /*{*/
            /*printf("%d  ", s->data);*/
            /*fflush(stdout);*/
            /*s = s->next;*/
        /*}*/
        /*printf("\n\r");*/
        /*sleep(1);*/
        /*stack_push(&demo_stack,i);*/
    /*}*/
    /*for(i = 0; i < 6; i++)*/
    /*{*/
        /*node* s;*/
        /*s = demo_stack.head;*/
        /*while(s != NULL)*/
        /*{*/
            /*printf("%d  ", s->data);*/
            /*fflush(stdout);*/
            /*s = s->next;*/
        /*}*/
        /*printf("\n\r");*/
        /*sleep(1);*/
        /*stack_pop(&demo_stack);*/
    /*}*/
/*}*/
