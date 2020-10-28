#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<sys/sem.h>
#include<unistd.h>

union semun
{
	int val;
	struct semid_ds *buf;
	ushort* array;
}arg;

int main()
{
	key_t k1=1234,k2=1000;
	char c;
	int *rc;
	int i,semid,n_sems=2,wrt=0,mutex=1,shmid;
	semid=semget(k1,n_sems,IPC_CREAT | 0666);

	shmid = shmget(k2,sizeof(int),IPC_CREAT|0666);	
	rc = (int *)shmat(shmid,NULL,0);

	(*rc) = 0;

	semctl(semid,wrt,SETVAL,1);
	semctl(semid,mutex,SETVAL,1);

	while((c=getchar()) != 'q')
	{
		continue;
	}

	shmdt(rc);
  	shmctl(shmid,IPC_RMID,NULL);

	semctl(semid,0,IPC_RMID,0);
	
	return 0;
}