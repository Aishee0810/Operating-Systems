#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>

int max(int x,int y,int z)
{
	if (x>=y && x>=z)
		return x;
	else if(y>=x && y>=z) 
		return y;
	else if(z>=x && z>=y)
		return z;
}

void shell_init()
{
	char dir[50];
	getcwd(dir,sizeof(dir));
	printf("\033[0;32m");
	printf("%s@shell2.0:~%s$ ",getenv("USER"),dir);
	printf("\033[0;31m");
}

char intcmd[10][10] ={"cd","pwd","clear","exit","echo"};
char extcmd1[10][10] ={"mkdir","ls","cat","date"};
char extcmd2[10][10]={"vi","wc","whoami"};

int check_cmd(char *cmd)
{
	int i;
	for(i=0;i<max(sizeof(intcmd),sizeof(extcmd1),sizeof(extcmd2));i++)
	{
		if(strcmp(cmd,intcmd[i])==0)
		{
			
			*cmd=*intcmd[i];
			return 1;
		}
		else if(strcmp(cmd,extcmd1[i])==0)
		{	
			 *cmd=*extcmd1[i];
			return 2;
		}
		else if(strcmp(cmd,extcmd2[i])==0)
		{
			//printf("same-%d",i);
			 *cmd=*extcmd2[i];
			return 3;
		}
	}
	return 1;
}
int pi(char *cmd)
{
    int pfd[2];
    char *c1=(char *)malloc(100 * sizeof(char));
    char *c2=(char *)malloc(100 * sizeof(char));
    int i=0,j=0,k=0,p=0;
    for(i=0;i<strlen(cmd);i++)
    {
        if(cmd[i]=='|')
        {
            printf("%s\n",cmd );
	    p =1;
            continue;
        }
        if(p==0)
        {
            c1[j]=cmd[i];
            j++;
        }
        else
        {
            c2[k]=cmd[i];
            k++;
        }
    }
    c1[j]=0;
    c2[k]=0;
    if(fork()==0)
    {
        if(pipe(pfd)==-1)
        {
            printf("Failure\n");
            return 0;
        }
        if(fork()==0)
        {
            close(pfd[0]);
            dup2(pfd[1],1);
            close(pfd[1]);
            char *cmd1=(char *)malloc(100 * sizeof(char));
            char *cmd2=NULL;
            for(i=0;i<strlen(cmd1);i++)
            {
                if(c1[i]==' ')
                {
                    cmd1[i]=0;
                    break;
                }
                cmd1[i]=c1[i];
            }
   
            if(strlen(c1)!=strlen(cmd1))
            {
                cmd2 = c1+i+1;
                cmd2[strlen(c1)-strlen(cmd1)-1] = 0;
            }
            char e_cmd1[25]="/bin/";
            strcat(e_cmd1,cmd1);
            char *a[]={e_cmd1,cmd2,0};
            if(execvp(a[0],a)<0)
            {
                printf("Failure!!\n");
                return 0;
            }
        }
        else
        {
           
            wait(NULL);       
            close(pfd[1]);
            dup2(pfd[0],0);
            close(pfd[0]);
            char *cmd1=(char *)malloc(100 * sizeof(char));
            char *cmd2=NULL;
            for(i=0;i<strlen(c2);i++)
            {
                if(c2[i]==' ')
                {
                    cmd1[i]=0;
                    break;
                }
                cmd1[i]=c2[i];
            }
   
            if(strlen(c2)!=strlen(cmd1))
            {
                cmd2 = c2+i+1;
                cmd2[strlen(c2)-strlen(cmd1)-1] = 0;
            }
            char e_cmd2[25]="/usr/bin/";
            strcat(e_cmd2,cmd1);
            char *b[]={e_cmd2,c2,0};
            if(execvp(b[0],b)<0)
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




int execute(char *cmd)
{

	int i,j=0;
	char *c1=(char*)malloc(100*sizeof(char));
	char *c2=NULL;
//	printf("%s\n",cmd);
	int len=strlen(cmd);
	int count=0,p=1;

	for(i=0;i<len;i++)
	{
		if(cmd[i]==' ')
		{
			for(j=i+1;j<len;j++)
			{
				if(cmd[j]=='|')
				{
					return pi(cmd);
				}
			}
		c1[i]='\0';
		break;
		}
		 else if(cmd[i]=='|')
		 	return pi(cmd);
		c1[i]=cmd[i];
	}
	
	if(strlen(cmd)!=strlen(c1))
	{
	c2=(cmd+i+1);
	c2[strlen(cmd)-strlen(c1)-1]='\0';
	}

	int cmp;

	if(strcmp(c1,"cd")==0)
		chdir(c2);
	else if(strcmp(c1,"exit")==0)
	{
		printf("Exiting...\n");
		exit(0);
	}

    else{
	if((cmp=check_cmd(c1))==1)
	{
		//printf("\n%d",cmp);
		int status=system(cmd)+1;
		
		return status;
	}
	else if((cmp=check_cmd(c1))==2||(cmp=check_cmd(c1))==3)
 	{
	//	printf("CMP-%d\n",cmp);
		pid_t pid;
		///printf("%d",cmp);
		if((pid=fork())==0)
		{	
			char e_cmd1[20]="/bin/";
			char e_cmd2[20]="/usr/bin/";
			//printf("%d",cmp);
			if(cmp==2)
			{
				strcat(e_cmd1,c1);
				char *s[]={e_cmd1,c2,0};
				
				if(execvp(s[0],s)<0)
			{
				printf("Failed Exec\n");
				return 0;
			}	
			}
			else if(cmp==3)
			{
				strcat(e_cmd2,c1);
				char *s[]={e_cmd2,c2,0};
				if(execvp(s[0],s)<0)
			{
				printf("Failed Exec\n");
				return 0;
			}
			}
			
		}
		else if(pid>0)
		{
			wait(NULL);
			printf("%d",cmp);
		}
		else 
			printf("Fork Error\n");
	}	
}
return 1;
}


int main()
{
	while(1)
	{
		shell_init();
		char c[50];
		fgets(c,50,stdin);
		c[strlen(c)-1]='\0';

		int count=0;
		int i=0,j=0;
		int parse_pos[50];
		//printf("%ld",strlen(cmd));
		
		for(i=0;i<strlen(c);i++)
		if(c[i]==';'||(c[i]=='&'&&c[i+1]=='&')||(c[i]=='|'&&c[i+1]=='|'))
		{
			if((c[i]=='&'&&c[i+1]=='&')||(c[i]=='|'&&c[i+1]=='|'))
			{
				parse_pos[count]=i;
				count++;
				i++;
			}
			else
			{
				parse_pos[count]=i;
				count++;
			}
		}
		parse_pos[count]=strlen(c);

		if(count==0)
		//printf("%s\n",cmd);
		execute(c);
		else
		{

		int k=0;
		char *cmd[count+1];
		int ret=1;

		for(i=0;i<count+1;i++)
			cmd[i]=(char *)malloc(20*sizeof(char));

		for(i=0;i<count+1;i++)
		{
			if(c[k]=='&')
			{
				cmd[i]=(c+k+1);
				cmd[i][parse_pos[i]-k-1]='\0';
				k=parse_pos[i]+1;
				if(ret==1)
				{
					ret=execute(cmd[i]);
				}
			}
			else if(c[k]=='|')
			{
				cmd[i]=(c+k+1);
				cmd[i][parse_pos[i]-k-1]='\0';
				k=parse_pos[i]+1;
				if(ret!=1)
					ret=execute(cmd[i]);
			}
			else
			{
				cmd[i]=(c+k);
				cmd[i][parse_pos[i]-k]='\0';
				k=parse_pos[i]+1;
				ret=execute(cmd[i]);					
			}
		//	printf("%s\n",comd[i]);
		}
		}
	}
}
