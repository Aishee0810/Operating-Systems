#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void main()
{
	char c[50],ch,x=0;
//	printf("Enter string:");	
        while((ch=getchar()) != EOF)
	{
	    fflush(stdin);
            c[x]=ch;
	    x++;
	}
	c[x]='\0';
	printf("%s ",c);
	//printf("\nMessage Received!");
}

