#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/sem.h>
#include<unistd.h>
#include<fcntl.h>
#define size 100
union semun {
int val;
struct semid_ds *buf;
ushort * array;
} arg; // declares a semun named arg
int main()
{
	key_t key=6021,key1=1234;
	int i,sem_id,nsems=2,*count,shm_id,mutex=1,wrt=0;
	shm_id=shmget(key1,sizeof(int),IPC_CREAT|0666);
	sem_id=semget(key,nsems,IPC_CREAT|0666);
	count=(int*)shmat(shm_id,NULL,0);
	*count = 0;
	char p;
	semctl(sem_id,mutex,SETVAL,1);
	semctl(sem_id,wrt,SETVAL,1);
	while((p=getchar())!='e')
	{		
		continue;
	}
	shmdt(count);
	shmctl(shm_id,IPC_RMID,NULL);
	semctl(sem_id,0,IPC_RMID,0);
	return 0;
}