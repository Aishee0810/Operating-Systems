#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
	int a,b;
	printf("\nThe process id is:%d.",getpid());
	printf("\nEnter two numbers to find their sum:");
	scanf("%d %d",&a,&b);
	printf("The sum of %d and %d is:%d.\n",a,b,a+b);
	return 0;
}
