#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#define size 100
long int fact(int x)
{
	if(x==0 || x==1)
	{
		return 1;
	}
	else
		return (x*fact(x-1));
}
int main()
{
	int i;
        int shmid;
        key_t key;
        int *shm,*a;
        key=6021;
        if((shmid=shmget(key,size,IPC_CREAT |0666))<0)
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
	*(a+1)=2;//turn variable
	*(a+2)=0;// terminating variable
	for(i=1;i<=12;i++)
	{
		while(*(a+1)!=1)
		{
			;
		}
		printf("The factorial of %d is: %ld",*(a+0),fact(*(a+0)));
		printf("\n");
		*(a+1)=2;
	}
	shmdt(a);
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}
