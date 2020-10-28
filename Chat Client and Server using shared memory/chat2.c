#include<signal.h>
#include<stdio.h>
#include<sys/ipc.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/shm.h>

#define SHMSIZE 10

static void signal_handler(int);
int pid1;
char *shm;

int main(int argc,  char *argv[])
{
    key_t key;
    key = atoi(argv[2]);
    int shmid;
    int i;

    shmid = shmget(key,SHMSIZE, IPC_CREAT | 0666);
    shm = shmat(shmid,NULL,0);

    signal(SIGUSR1,signal_handler);
    signal(SIGINT,signal_handler);

    printf("Process ID - %d\n",getpid());
    scanf("%d",&pid1);
   
    if(atoi(argv[1])==0)
    {
    printf("Enter the message : ");
    scanf("%s",shm);
    kill(pid1,SIGUSR1);
    }

        while(1)
        {
            ;
        }

    return 0;
       
}

static void signal_handler(int signum)
{
    switch(signum)
    {
        case SIGUSR1:
            printf("Message received : ");
            printf("%s\n",shm);
            printf("Enter the message : ");
            scanf("%s",shm);
            kill(pid1,SIGUSR1);
            break;
	case SIGINT:
            printf("Session Expired.\n");
            exit(0);

    }
}
