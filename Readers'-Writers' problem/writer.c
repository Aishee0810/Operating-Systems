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
	int i,semid,n_sems=2,wrt=0,mutex=1;
	semid=semget(k1,n_sems,IPC_CREAT | 0666);

	int fd = open("sample.txt", O_WRONLY | O_CREAT);

	wait(semid,wrt);

	char *c = (char *) malloc (100 * sizeof(char));
	printf("Enter text:");
	fgets(c,100,stdin);
	//gets(c);
	write(fd, c, strlen(c));
	printf("%s\n",c);
	close(fd);

	signal(semid,wrt);

	return 0;
}