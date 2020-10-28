#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
int fact(int x)
{
	int f=1,i;
	if(x==0 || x==1)
	{
		return 1;
	}
	else
	{
                for(i=1;i<=x;i++)
                {
                        f=f*i;
                }
        return f;
	}
}

int main(int argc,char *argv[])
{
	int k;
	for(k=0;k<argc-1;k++)
	{
		if(fork()==0)
		{
		 	int arr=atoi(argv[k+1]);
			printf("Process id is:%d\n",getpid());
			int f=fact(arr);
			printf("The factorial of %d is: %d\n",arr,f);
			return 0;
		}
		else
			wait(NULL);
}
return 0;	
}

