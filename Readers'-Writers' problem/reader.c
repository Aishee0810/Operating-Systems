#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<sys/sem.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>

union semun
{
	int val;
	struct semid_ds *buf;
	ushort* array;
}arg;

void wait(int semid,int semnum)
{
	struct sembuf x;
	x.sem_num=semnum;
	x.sem_op=-1;
	x.sem_flg=0;
	semop(semid,&x,1);
}

void signal(int semid,int semnum)
{
	struct sembuf x;
	x.sem_num=semnum;
	x.sem_op=1;
	x.sem_flg=0;
	semop(semid,&x,1);
}

int main()
{
	key_t k1=1234,k2=1000;
	int i,s,semid,n_sems=2,wrt=0,mutex=1,shmid;
	int *rc;
	char a;
	semid=semget(k1,n_sems,IPC_CREAT | 0666);

	shmid = shmget(k2,sizeof(int),IPC_CREAT|0666);	
	rc = (int *)shmat(shmid,NULL,0);

	int fd = open("sample.txt", O_RDONLY | O_CREAT);
	printf("%d\n",*rc);
	wait(semid,mutex);
	(*rc) = (*rc) + 1;
	if((*rc) == 1)
		wait(semid,wrt);
	signal(semid,mutex);

	char *c = (char *) malloc (100 * sizeof(char));
	s = read(fd, c, 100);
	c[s] = '\0';
	printf("%s\n",c);
	close(fd);
	while((a=getchar()) != 'q')
		continue;


	wait(semid,mutex);
	(*rc) = (*rc) - 1;
	if((*rc) == 0)
	{
		shmdt(rc);
		signal(semid,wrt);
	}
	signal(semid,mutex);

	return 0;
}