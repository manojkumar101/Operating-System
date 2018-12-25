#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<semaphore.h>

int  rc=0;
sem_t w,m;
void *reader(void *arg)
{
	 int i=(int)arg;
	printf("%d Reader is created  \n", i);
	sleep(10);
	sem_wait(&m);
	rc++;
	if(rc==1)
		sem_wait(&w);
	sem_post(&m);
	printf("%d reading by the Reader  \n", i);
	
	sleep(5);
	
	sem_wait(&m);
	rc--;
	
	if(rc==0)
		sem_post(&w);
	sem_post(&m);
	printf("%d reader completed\n",i); 		
}

void *writer(void *arg)
{
	int i=(int) arg;
	printf("%d Writter is created  \n", i);
	sleep(10);
	sem_wait(&w);	
	printf("%d writing by Writer \n",i);
	
	sleep(5);
	sem_post(&w);
	printf("%d Writer completed\n",i);
}

int main()
{	int i,b;
	pthread_t r_id[5],w_id[5];
	sem_init(&m,0,1);
	sem_init(&w,0,1);
	sleep(2);
	for(i=1;i<=3;i++)
	{
		pthread_create(&w_id[i],NULL,writer,(void *)i);sleep(1);
		pthread_create(&r_id[i],NULL,reader,(void *)i);sleep(1);		
		
	}
	for(i=1;i<=3;i++)
	{
		pthread_join(w_id[i],NULL);
		pthread_join(r_id[i],NULL);
	}

	return 0;
}
