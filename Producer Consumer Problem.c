#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
int buff[5];
pthread_mutex_t m;
sem_t empty,full;
void *prod(void *arg)
{
      int item=10,i=0;
      printf("\nproducer thread is created\n");
      sleep(5);
            
          while(1)
          {
           sem_wait(&empty);
           pthread_mutex_lock(&m);
           buff[i++]=item;
            printf("\n%d item inserted at position %d\n",item,i-1);
           if(i==5)
            i=0;
          
           sleep(1);
           pthread_mutex_unlock(&m);
           sem_post(&full);
           
          } 
}
void *cons(void *arg)
{     
      int key,i=0;
      printf("\nconsumer thread is created\n");
      
      sleep(3);
      while(1)
    {

      sem_wait(&full);
      pthread_mutex_lock(&m);
      key=buff[i++];
      printf("\n%d item value  extracted at  from position %d\n",key,i-1);
      
      if(i==5)
            i=0;
      sleep(1);
      pthread_mutex_unlock(&m);
      sem_post(&empty);
      }
}
main()
{

      pthread_t pid,cid;
      sem_init(&empty,0,5);
      sem_init(&full,0,0);
      pthread_mutex_init(&m,NULL);
      pthread_create(&pid,NULL,prod,NULL);
      sleep(1);
      pthread_create(&cid,NULL,cons,NULL);
        sleep(1); 
        pthread_join(pid,NULL);   
      pthread_join(cid,NULL);
      printf("\n main thread is terminated\n");
}
