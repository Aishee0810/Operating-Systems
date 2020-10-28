#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/sem.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
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
	int i,sem_id,s,*count,nsems=2,mutex=1,wrt=0;
	int shm_id;
	char p;
	sem_id=semget(key,nsems,IPC_CREAT|0666);
	shm_id=shmget(key1,sizeof(int),IPC_CREAT|0666);
	count=(int*)shmat(shm_id,NULL,0);
	int fd=open("sample.txt", O_RDONLY | O_CREAT);
	printf("Number of readers:%d\n",(*count)+1);
	wait(sem_id,mutex);
	(*count)=(*count)+1;
	if((*count)==1)
		wait(sem_id,wrt);
	signal(sem_id,mutex);
	char *arr=(char*)malloc(100*sizeof(char));
	s=read(fd,arr,100);
	arr[s]='\0';
	printf("Read :%s",arr);
	close(fd);
	while((p=getchar())!='e')
		continue;
	wait(sem_id,mutex);
	(*count)=(*count)-1;
	if((*count)==0)
	{
		shmdt(count);
		signal(sem_id,wrt);
	}
	signal(sem_id,mutex);
	//shmdt(count);
	//shmctl(shm_id,IPC_RMID,NULL);
	return 0;
	}

