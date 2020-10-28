#include<stdio.h>
#include <sys/types.h> 
#include<stdio.h>
#include <unistd.h>
#include<sys/stat.h> 
#include<fcntl.h>
#include<string.h>
#include<sys/wait.h>
int main()
{
	pid_t cpid;
	char a[30];
	int m;
	printf("\nChoose:\n1.Read(Press 1)\n2.Write(Press 2)\n");
	scanf("%d",&m);
	if(m==1)
	{
    		int fd = open("fileass2.txt", O_RDONLY | O_CREAT);
		int i;
		cpid=fork();
    		if(cpid==0)	
		{
			printf("File Descriptor for child process with id %d:%d\n",getpid(),fd);
			read(fd,a,8);
			printf("%s\n",a);
		}
		else
		{
			printf("File Descriptor for parent process with id %d:%d\n",getppid(),fd);
                	read(fd,a,8);
			
                        printf("%s\n",a);
                        //wait(NULL);//child executes before parent
			//return(0);
			//close(fd);
		}
	}
	else if(m==2)
	{
		int fd1 = open("fileass2.txt", O_WRONLY | O_CREAT);
                int i;
                cpid=fork();
                if(cpid==0)
                {
                        printf("File Descriptor for child process with id %d:%d\n",getpid(),fd1);
                        //read(fd1,a,8);
			//write(fd1,"\nComputer",9);
						write(fd1," day(child)!",strlen("day(child)!"));
						printf("File Written into by child process.");
                
                }
                else
                {
                        printf("File Descriptor for parent process with id %d:%d\n",getppid(),fd1);
                        //read(fd1,a,8);
			//write(fd1," Science",8);
						write(fd1,"Good(parent)",strlen("Good(parent)"));
						printf("File Written into by parent process.\n");
                        close(fd1);
        }
        		//write(fd1,"Harry Potter",strlen("Harry Potter"));//parent and child both write


	return 0;
	}
}