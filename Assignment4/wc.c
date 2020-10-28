#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
void main(int argc,char *argv[])
{
	int c1=0,c3=0,i,x,y,z;
	char ch[500];
	int fd=0;
//        int fd=open("file.txt",O_RDONLY|O_CREAT);
	char choice[2];
//	printf("Enter choice:\n1.Lines()\n2.Words(2)\n3.Characters\n");
//	scanf("%s",choice);
	if(strcmp(argv[1],"-l")==0)
	{
//	fd=open("file.txt",O_RDONLY|O_CREAT);
 	 x=read(fd,ch,sizeof(ch));
	if(x!=0)
        	{
		for(i=0;i<x;i++)
			{
				if(ch[i]=='\n')
		{
			c1++;
			//++c1;
		}
			}
		}
	//printf("\nLines:%d\n",c1+1);
	printf("\nLines:%d\n",c1+1);
	}
	else if(strcmp(argv[1],"-w")==0)
	{
//	fd=open("file.txt",O_RDONLY|O_CREAT);
	 y=read(fd,ch,sizeof(ch));
	 if(y!=0)
	{
		for(i=0;i<y;i++)
			{
			if(ch[i]==' ' || ch[i]=='\n')
			{
				c3++;
			}
			}
			}
	 printf("\nWords:%d\n",c3+1);
	}
	else if(strcmp(argv[1],"-c")==0)
	{
			//fd=open("file.txt",O_RDONLY|O_CREAT);
			z=read(fd,ch,sizeof(ch));
			printf("\nCharacters:%d",z);
	}
}

 
