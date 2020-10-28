#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<unistd.h>

// char in[10][10] ={"clear","echo","exit","cd","pwd"};
// char ex_1[10][10] ={"cat","date","ls","mkdir"};
// char ex_2[10][10] ={"subl","whoami","vi","wc","tee"};

int pi(char *cd,int p)
{
	// printf("%d\n",p );
	int pfd[p][2];
	int i,sc[100];
	char *cmd[p+1];
	// printf("%s\n",cd);
	for(i=0;i<=p;i++)
	{
		cmd[i] = (char *)malloc(100 * sizeof(char));
	}
	int j=0,k=0,l=0,c=0;
	for(i=0;i<=p;i++)
	{
		l=0;
		for(j=k;j<strlen(cd);j++)
		{
			if((cd[j]=='|')||(cd[j]==0))
			{
				cmd[i][l]=0;
				k=j+1;
				break;
			}
			cmd[i][l]=cd[j];
			l++;
		}
	}
	// for(i=0;i<=p;i++)
	// {
	// 	printf("%s\n",cmd[i]);
	// }
	
	if(fork()==0)
	{
		if(pipe(pfd[0])==-1)
	 	{
			printf("Failure\n");
			return 0;
		}
		
		if(fork()==0)
		{
			for(i=1;i<p;i++)
			{
			// printf("%d\n",i+1);
			
				if(pipe(pfd[i])==-1)
	 			{
					printf("Failure\n");
					return 0;
				}
				if(fork() != 0)
				{
					// printf("%s else\n",cmd[i] );
					wait(NULL);
					close(pfd[i][1]);
					dup2(pfd[i][0],0);
					close(pfd[i][0]);

					close(pfd[i-1][0]);
					dup2(pfd[i-1][1],1);
					close(pfd[i-1][1]);

					char *cmdp1=(char *)malloc(100 * sizeof(char));
					char *cmdp4=(char *)malloc(100 * sizeof(char));
					char *cmdp2=NULL,*cmdp3=NULL;
					for(j=0;j<strlen(cmd[p-i]);j++)
					{
						if(cmd[p-i][j]==' ')
						{
							cmdp1[j]=0;
							break;
						}
						cmdp1[j]=cmd[p-i][j];
					} 
			
					if(strlen(cmd[p-i])!=strlen(cmdp1))
					{
						cmdp2 = cmd[p-i]+j+1;
						cmdp2[strlen(cmd[p-i])-strlen(cmdp1)-1] = 0;
					}
					if(cmdp2!=NULL)
					{
						for(j=0;j<strlen(cmdp2);j++)
						{
							if(cmdp2[j]==' ')
							{
								cmdp4[j]=0;
								break;
							}
							cmdp4[j]=cmdp2[j];
						} 
			
						if(strlen(cmdp2)!=strlen(cmdp4))
						{
							cmdp3 = cmdp2+j+1;
							cmdp3[strlen(cmdp2)-strlen(cmdp4)-1] = 0;
						}
					}
					else
						cmdp4 = cmdp2;
					char *pipe[]={cmdp1,cmdp4,cmdp3,0};
					if(execvp(pipe[0],pipe)<0)
					{
						printf("Failure!!\n");
						return 0;
					}
				}
			}
			close(pfd[i-1][0]);
			dup2(pfd[i-1][1],1);
			close(pfd[i-1][1]);

			char *cmdp1=(char *)malloc(100 * sizeof(char));
			char *cmdp4=(char *)malloc(100 * sizeof(char));
			char *cmdp2=NULL,*cmdp3=NULL;
			for(j=0;j<strlen(cmd[p-i]);j++)
			{
				if(cmd[p-i][j]==' ')
				{
					cmdp1[j]=0;
					break;
				}
				cmdp1[j]=cmd[p-i][j];
			} 
		
			if(strlen(cmd[p-i])!=strlen(cmdp1))
			{
				cmdp2 = cmd[p-i]+j+1;
				cmdp2[strlen(cmd[p-i])-strlen(cmdp1)-1] = 0;
			}
			if(cmdp2!=NULL)
			{
				for(j=0;j<strlen(cmdp2);j++)
				{
					if(cmdp2[j]==' ')
					{
						cmdp4[j]=0;
						break;
					}
					cmdp4[j]=cmdp2[j];
				} 
			
				if(strlen(cmdp2)!=strlen(cmdp4))
				{
					cmdp3 = cmdp2+j+1;
					cmdp3[strlen(cmdp2)-strlen(cmdp4)-1] = 0;
				}
			}
			else
				cmdp4 = cmdp2;
			char *pipe[]={cmdp1,cmdp4,cmdp3,0};
			if(execvp(pipe[0],pipe)<0)
			{
				printf("Failure!!\n");
				return 0;
			}
		}
		else
		{
			wait(NULL);
			// printf("wait\n");
			close(pfd[0][1]);
			dup2(pfd[0][0],0);
			close(pfd[0][0]);

			char *cmdp1=(char *)malloc(100 * sizeof(char));
			char *cmdp4=(char *)malloc(100 * sizeof(char));
			char *cmdp2=NULL,*cmdp3=NULL;
			for(j=0;j<strlen(cmd[p]);j++)
			{
				if(cmd[p][j]==' ')
				{
					cmdp1[j]=0;
					break;
				}
				cmdp1[j]=cmd[p][j];
			} 
		
			if(strlen(cmd[p])!=strlen(cmdp1))
			{
				cmdp2 = cmd[p]+j+1;
				cmdp2[strlen(cmd[p])-strlen(cmdp1)-1] = 0;
			}
			if(cmdp2!=NULL)
			{
				for(j=0;j<strlen(cmdp2);j++)
				{
					if(cmdp2[j]==' ')
					{
						cmdp4[j]=0;
						break;
					}
					cmdp4[j]=cmdp2[j];
				} 
			
				if(strlen(cmdp2)!=strlen(cmdp4))
				{
					cmdp3 = cmdp2+j+1;
					cmdp3[strlen(cmdp2)-strlen(cmdp4)-1] = 0;
				}
			}
			else
				cmdp4 = cmdp2;
			char *pipe[]={cmdp1,cmdp4,cmdp3,0};
			if(execvp(pipe[0],pipe)<0)
			{
				printf("Failure!!\n");
				return 0;
			}

		}
	}
	else
		wait(NULL);
	return 1;
}

int exe(char *cd)
{
	// printf("kk %ld\n",strlen(cd));
	int i=0,j=0,c=0,len=strlen(cd),max,p=0,k=0,x;

	char *cmd1=(char *)malloc(100 * sizeof(char));
	char *cmd4=(char *)malloc(100 * sizeof(char));
	char *cmd2=NULL,*cmd3=NULL;

	for(i=0;i<len;i++)
	{
		if(cd[i]==' ')
		{
			// printf("space\n");
			for(j=i+1;j<len;j++)
			{
				if(cd[j]=='|')
				{
					p++;
					for(k=j+1;k<len;k++)
					{
						if(cd[k]=='|')
						{
							p++;
						}	
					}

					x = pi(cd,p);
					// printf("%d\n",x );
					return x;
				}
			}
			cmd1[i]=0;
			break;
		}
		else if(cd[i]=='|')
		{
			// printf("pipe\n");
			p++;
			for(k=i+1;k<len;k++)
			{
				if(cd[k]=='|')
				{
					p++;
				}	
			}
		   	x = pi(cd,p);
			// printf("%d\n",x );
			// exit(0);
			return x;
		}
		cmd1[i]=cd[i];
	} 
	
	if(strlen(cd)!=strlen(cmd1))
	{
		cmd2 = cd+i+1;
		cmd2[strlen(cd)-strlen(cmd1)-1] = 0;
	}
	// printf("%s\n%s\n%s\n",cmd1,cmd2,cmd3);

	if(cmd2!=NULL)
	{
		for(j=0;j<strlen(cmd2);j++)
		{
			if(cmd2[j]==' ')
			{
				cmd4[j]=0;
				break;
			}
				cmd4[j]=cmd2[j];
		} 
			
		if(strlen(cmd2)!=strlen(cmd4))
		{
			cmd3 = cmd2+j+1;
			cmd3[strlen(cmd2)-strlen(cmd4)-1] = 0;
		}
	}
	else
		cmd4 = cmd2;
	// printf("kkkkkk\n");

	// printf("%s\n%s\n%s\n",cmd1,cmd2,cmd3 );
	if(strcmp(cmd1,"cd") == 0)
	{
		if(cmd2 == NULL)
			chdir(getenv("HOME"));
		else
			chdir(cmd2);
	}
	else if(strcmp(cmd1,"exit") == 0)
		exit(0);
    else
    {
		if(fork()==0)
		{	
			char *func[]={cmd1,cmd4,cmd3,0};
			if(execvp(func[0],func)<0)
			{
				printf("Failure!!\n");
				return 0;
			}
		}
		else
			wait(NULL);	
	}
	return 1;
}

int main()
{
	char pwd[100],cad[100],cd[100];
	int sc[100],c=0,i=0,j=0,k=0;
	while(1)
	{
		bzero(pwd, sizeof(pwd));
    	getcwd(pwd,sizeof(pwd));
    	printf("\033[22;31m%s@mysh:~%s$ ",getenv("USER"),pwd);
    	printf("\033[22;34m");
    	// fflush(stdin);
    	bzero(cad, sizeof(cad));
        fgets(cad,100,stdin);
       	cad[strlen(cad)-1] = 0;

       	bzero(cd, sizeof(cd));
       	i=0;j=0;
       	while(cad[i] != 0)
       	{
       		if((cad[i]==';') || (cad[i]=='&') || (cad[i]=='|'))
       		{
       			if((cad[i-1]==' ') && (cad[i+1]==' ') && (cd[j-1]==' '))
       			{
       				j--;
       				cd[j]=cad[i];
       				j++;
       				i+=2;
       			}
       			else if((cad[i-1]==' ') && (cd[j-1]==' '))
       			{
       				j--;
       				cd[j]=cad[i];
       				j++;
       				i++;
       			}
       			else if(cad[i+1]==' ')
       			{
       				cd[j]=cad[i];
       				i+=2;
       				j++;
       			}
       			else
       			{
       				cd[j]=cad[i];
       				i++;
       				j++;
       			}
       			continue;
       		}
       		cd[j]=cad[i];
       		i++;
       		j++;
       	}

        bzero(sc, sizeof(sc));
        c=0;i=0;j=0;
        for(i=0;i<strlen(cd);i++)
		{
			if(cd[i]==0)
			{	
				sc[c]=i;
			}
			else if((cd[i]==';') || ((cd[i]=='&') && (cd[i+1]=='&')) || ((cd[i]=='|') && (cd[i+1]=='|')))
			{
				if(((cd[i]=='&') && (cd[i+1]=='&')) || ((cd[i]=='|') && (cd[i+1]=='|')))
				{
					sc[c]=i;
					c++;
					i++;
				}
				else
				{
					sc[c]=i;
					c++;
				}
			}
		}
		int id=0;
		if(c==0)
			id = exe(cd);
		else
		{
			k=0;
			char *icd[c+1];
			
			for(i=0;i<=c;i++)
				icd[i] = (char *)malloc(25 * sizeof(char));

			for(i=0;i<=c;i++)
			{

				if(cd[k]=='&')
				{
					icd[i] = cd+k+1;
					icd[i][sc[i]-k-1] = 0;
					k = sc[i]+1;
					if(id==1)
						id = exe(icd[i]);
					
				}
				else if(cd[k]=='|')
				{
					icd[i] = cd+k+1;
					icd[i][sc[i]-k-1] = 0;
					k = sc[i]+1;
					if(id!=1)
						id = exe(icd[i]);
				}
				else
				{
					icd[i] = cd+k;
					icd[i][sc[i]-k] = 0;
					k = sc[i]+1;
					id = exe(icd[i]);					
				}
			}
		}
		// printf("%d\n",id );
	}
	return 0;
}