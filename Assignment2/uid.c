#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
void main()
{
        printf("Real user id:%d\n",getuid());
        printf("Effective user id:%d\n",geteuid());
        int fd;
        char *x= (char*)malloc(25*sizeof(char));
        fd=open("sample.txt",O_RDONLY);
        read(fd,x,10);
        printf("\n%s",x);
}

