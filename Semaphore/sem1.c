#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/sem.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#define size 100
union semun
 {
	int val;
	struct semid_ds *buf;
	ushort * array;
} arg; // declares a semun named arg
void wait(int semid,int semnum)
{
	//printf("Inside wait.\n");
	struct sembuf b;
	b.sem_num=semnum;
	b.sem_op=-1;
	b.sem_flg=0;
	semop(semid,&b,1);
}

void signal(int semid,int semnum)
{
	//printf("Inside signal:\n");
	struct sembuf b;
	b.sem_num=semnum;
	b.sem_op=1;
	b.sem_flg=0;
	semop(semid,&b,1);
}
int main()
{
	key_t key=6021,key1=1234;
	int i,sem_id,shm_id,nsems,*count,s;
	nsems=2;
	int mutex=1;
	int wrt=0;
	sem_id=semget(key,nsems,IPC_CREAT|0666);
	//shm_id=shmget(key1,sizeof(int),IPC_CREAT|0666);
	//count=(int*)shmat(shm_id,NULL,0);
	//*count=0;
	int fd=open("sample.txt", O_WRONLY | O_CREAT);
	//printf("Semid is:%d\n",sem_id);
	//printf("Shmid is:%d\n",shm_id);
	wait(sem_id,wrt);
	char *w=(char *)malloc(50*(sizeof(char)));
	printf("\nEnter some text:");
	fgets(w,50,stdin);
	write(fd,w,strlen(w));
	printf("%s\n",w);
	close(fd);
	printf("Written by:%d",getpid());
	signal(sem_id,wrt);
	return 0;
}



