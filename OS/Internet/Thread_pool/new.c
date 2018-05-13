#include <stdio.h>
#include <stdlib.h>
#include
     f("im bolckinged_cond_wait (&(pool->queue_ready), &(pool->queue_lock));
                 }
                 
                         /*线程池要销毁了*/
                         if (pool->shutdown)
                         {
                                     /*遇到break,continue,return等跳转语句，千万不要忘记先解锁*/
                                     pthread_mutex_unlock (&(pool->queue_lock));
                                                 printf ("thread 0x%x will exit\n", pthread_self ());
                                                             pthread_exit (NULL);
                                                                     
                         }
                         
                                 printf ("thread 0x%x is starting to work\n", pthread_self ());
                                 
                                         /*assert是调试的好帮手*/
                                         assert (pool->cur_queue_size != 0);
                                                 assert (pool->queue_head != NULL);
                                                         
                                                         /*等待队列长度减去1，并取出链表中的头元素*/
                                                         pool->cur_queue_size--;
             CThread_worker *worker = pool->queue_head;
                     pool->queue_head = worker->next;
                             pthread_mutex_unlock (&(pool->queue_lock));
                             
                                     /*调用回调函数，执行任务*/
                                     (*(worker->process)) (worker->arg);
                                             free (worker);
                                                     worker = NULL;
                                                         }
    /*�<M-Space>一句应该是不可达的*/
    pthread_exit (NULL);
    }

//    下面是测试代码
//
//    void *
//    myprocess (void *arg)
//    {
//        printf ("threadid is 0x%x, working on task %d\n", pthread_self (),*(int *) arg);
//            sleep (1);/*休息一秒，延长任务的执行时间*/
//                return NULL;
//                }
//
//                int
//                main (int argc, char **argv)
//                {
//                    pool_init (3);/*线程池中最多三个活动线程*/
//                        
//                            /*连续向池中投入10个任务*/
//                                int *workingnum = (int *) malloc (sizeof (int) * 10);
//                                    int i;
//                                        for (i = 0; i < 10; i++)
//                                            {
//                                                    workingnum[i] = i;
//                                                            pool_add_worker (myprocess, &workingnum[i]);
//                                                                }
//                                                                    /*等待所有任务完成*/
//                                                                        sleep (5);
//                                                                            /*销毁线程池*/
//                                                                                pool_destroy ();
//
//                                                                                    free (workingnum);
//                                                                                        return 0;
//                                                                                        }
//                                                                                        
//                                            }
//                }
//    }")here?\n");
