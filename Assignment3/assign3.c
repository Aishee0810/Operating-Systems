#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<string.h>
int main(int argc,char *argv[])
{
	int k;
	for(k=1;k<argc;k++)
	{
		char a[200];
		a[0]='.';// add
		a[1]='/';//'./'  to each argv[k]
		a[2]='\0';
		char *p[]={argv[k]};
	    strcat(a,p[0]);
		char *arr[]={a,NULL};
		//char *arr[]={argv[k],NULL};//character array stores file pointers and a null character to indicate end of pointer
		if(fork()==0)
		{
			printf("The child process id is:%d.\n",getpid());//prints process id for each task
			execvp(arr[0],arr);//executes each task
		}
		else
			wait(NULL);
	}
	return 0;
}
