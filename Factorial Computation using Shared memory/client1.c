#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#define shmsize 100
int main()
{
        int c;
        int shmid;
        key_t key;
        int *shm,*s;
        key=5678;
        if((shmid=shmget(key,shmsize,IPC_CREAT|0666))<0)
        {
                perror("shmget");
                exit(1);
        }
        if((shm=shmat(shmid,NULL,0))==(int *)-1)
        {
                perror("shmat");
                exit(1);
        }
s=shm;
        for(c=1;c<=12;c++)
        {*s++=c;
                *s=0;
        }
                while(*shm!='*')
                sleep(1);
        return 0;
}


