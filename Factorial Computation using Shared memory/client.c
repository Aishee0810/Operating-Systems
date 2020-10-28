#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#define size 100
int main()
{
	int i;
	int shmid;
	key_t key;
	int *shm,*a;
	key=6021;
	if((shmid=shmget(key,sizeof(int)*3,IPC_CREAT |0666))<0)
	{
		perror("shmget");
		exit(1);
	}
	if((shm=shmat(shmid,NULL,0))==(int *)-1)
	{
		perror("shmat");
		exit(1);
	}
	a=shm;
	*(a+1)=1;
	*(a+2)=0;
	for(i=1;i<=12;i++)
	{
		*(a+0)=i;
		printf("Number whose factorial is to be computed:%d\n",*(a+0));
		while(*(a+1)!=2)
		{
			;
		}

		*(a+1)=1;
	}
	shmdt(a);
	shmctl(shmid,IPC_RMID,NULL);	
	return 0;
}
