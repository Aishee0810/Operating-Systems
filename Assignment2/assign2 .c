#include<stdio.h>
#include <sys/types.h> 
#include<stdio.h>
#include <unistd.h>
#include<sys/stat.h> 
#include<fcntl.h>
int main()
{
	pid_t cpid;
	char a[30];
	int m;
	printf("\nChoose:\nRead(Press 1)\n2.Write(Press 2)\n");
	scanf("%d",&m);
	if(m==1)
	{
    		int fd = open("file.txt", O_RDONLY | O_CREAT);
		int i;
		cpid=fork();
    		if(cpid==0)	
		{
			printf("File Descriptor for child process with id:%d\n",getpid(),fd);
			read(fd,a,8);
		//	for(i=0;i<30;i++)
			printf("%s\n",a);
		}
		else
		{
			printf("File Descriptor for parent process with id %d:%d\n",getppid(),fd);
                	read(fd,a,8);
			//	for(i=0;i<30;i++)
                        printf("%s\n",a);
			//return(0);
			//close(fd);
		}
	}
	else if(m==2)
	{
		int fd1 = open("file.txt", O_WRONLY | O_CREAT);
                int i;
                cpid=fork();
                if(cpid==0)
                {
                        printf("File Descriptor for child process with id %d:%d\n",getpid(),fd1);
                        read(fd1,a,8);
			//write(fd1,"\nComputer",9);
			write(fd1," Mechanics(child)",10);
			printf("File Written into by child process.");
                //      for(i=0;i<30;i++)
                        printf("%s\n",a);
                }
                else
                {
                        printf("File Descriptor for parent process with id %d:%d\n",getppid(),fd1);
                        read(fd1,a,8);
			//write(fd1," Science",8);
			write(fd1," Engineering(parent)",12);
			printf("File Written into by parent process.");
                        //      for(i=0;i<30;i++)
                        printf("%s\n",a);
                        //return(0);
                        close(fd1);
        }


	return 0;
	}
}
