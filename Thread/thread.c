#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/sem.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<pthread.h>
int buffer=0;
pthread_mutex_t mutex;
//pthread_barrier_t bar;
void *func()
{
	int count=0;

	while(buffer < 22)
	{
		sleep(0.67);
		//pthread_barrier_wait(&bar);
		pthread_mutex_lock(&mutex);
		printf("Thread ID:%lu\n", pthread_self());
		printf("Process ID:%u\n", getpid());
		printf("Buffer value:%d\n", buffer++);
		count++;
		pthread_mutex_unlock(&mutex);
	}

	printf("Thread ID:%lu\nNumber of times buffer is modified:%d\n",pthread_self(),count);
}

int main()
{
	pthread_t t1,t2,t3;
	//pthread_barrier_init(&bar,NULL,3);
	pthread_mutex_init(&mutex,NULL);
	pthread_create(&t1,NULL,func,NULL);
	pthread_create(&t2,NULL,func,NULL);
	pthread_create(&t3,NULL,func,NULL);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);

	return 0;
}