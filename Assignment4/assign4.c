#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
int main(int argc, char* argv[])
{
	int pfd[2];
	if(fork()==0)
	{
		pipe(pfd);
		if(fork()==0)
		{
			close(pfd[0]);
			dup2(pfd[1],1);
			close(pfd[1]);
			char *arr[]={"./write2",argv[1],'\0'};
			execvp(arr[0],arr);
		}
		else 
		{
			close(pfd[1]);
			dup2(pfd[0],0);
			close(pfd[0]);
			char *arr1[]={"./wc",argv[1],'\0'};
			execvp(arr1[0],arr1);
		}
	}
	else
	 wait(NULL);
	return 0;
}	
	
 