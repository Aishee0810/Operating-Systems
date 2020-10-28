#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
//gcd of two numbers
int gcd(int a,int b)
{
	if(b==0)
		return a;
	else return gcd(b,a%b);
}
int main()
{
	int x,y;
	printf("The process id is:%d",getpid());
	printf("\nEnter two numbers whose HCF you want:");
	scanf("%d %d",&x,&y);
	//printf("%d %d",x,y);
	printf("The gcd of the two numbers is:%d.\n",gcd(x,y));
	printf("\n");
}
