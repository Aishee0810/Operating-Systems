#include<stdio.h>
#include<sys/ipc.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/shm.h>
#define SHMSIZE 100
#define m 4
#define n 4
typedef struct
{
	//int m,n;
	int B[m][n];
}matrix;
int main()
{
	key_t key;
	key=1234;
	matrix *shm;
//	int **B;
//	int m,n;
	int A[m][n];
/*	printf("Enter number of rows for matrix:\n");
	scanf("%d",&m);
	printf("Enter number of columns for matix:\n");
	scanf("%d",&n);*/
	int i,j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("A[%d][%d]:",i,j);
			scanf("%d",&A[i][j]);
		}
	}
	printf("Supplied matrix:\n");
	for(i=0;i<m;i++)
        {
                for(j=0;j<n;j++)
                {
                       // printf("Enter data:");
                        printf("%d",A[i][j]);
                }
		printf("\n");
        }

	int shmid;
        shmid = shmget(IPC_PRIVATE,SHMSIZE, IPC_CREAT | 0666);
    	shm = (matrix*)shmat(shmid,NULL,0);
        for(i=0;i<m;i++)
        {
		for(j=0;j<n;j++)
		{
			if(fork()==0)
			{
				int sum;
			//	shmid = shmget(key,SHMSIZE, IPC_CREAT | 0666);
        		//	shm = shmat(shmid,NULL,0);
				if(i==0)
				{
					if(j==0)
					{
						sum=A[i][j]+A[i+1][j]+A[i][j+1]+A[i+1][j+1];
						sum=sum/4;
						shm->B[i][j]=sum;
						exit(0);
					}
					else if(j==n-1)
					{
						sum=A[i][j]+A[i+1][j-1]+A[i][j-1]+A[i+1][j];
						sum=sum/4;
						shm->B[i][j]=sum;
						exit(0);
					}
					else
					{
						sum=A[i][j]+A[i][j-1]+A[i][j+1]+A[i+1][j-1]+A[i+1][j]+A[i+1][j+1];
						shm->B[i][j]=sum/6;
						exit(0);
					}
				}
				else if(i==m-1)
				{
					if(j==0)
					{
						sum=A[i][j]+A[i-1][j]+A[i-1][j+1]+A[i][j+1];
						sum=sum/4;
						shm->B[i][j]=sum;
						exit(0);
					}
					else if(j==n-1)
					{
						sum=A[i][j]+A[i][j-1]+A[i-1][j]+A[i-1][j-1];
						sum=sum/4;
						shm->B[i][j]=sum;
						exit(0);
					}
					else 
					{
						sum=A[i][j]+A[i][j-1]+A[i][j+1]+A[i-1][j-1]+A[i-1][j]+A[i-1][j+1];
						sum=sum/6;
						shm->B[i][j]=sum;
						exit(0);
					}
				}
				else if(i!=0 && j==0)
				{
					sum=A[i][j]+A[i][j+1]+A[i-1][j]+A[i-1][j+1]+A[i+1][j+1]+A[i+1][j];
					sum=sum/6;
					shm->B[i][j]=sum;
					exit(0);
				}
				else if(i!=m-1 && j==n-1)
				{
					sum=A[i][j]+A[i][j-1]+A[i-1][j]+A[i-1][j-1]+A[i+1][j]+A[i+1][j-1];
					sum=sum/6;
					shm->B[i][j]=sum;
					exit(0);
				}
				else
				{
					sum=A[i-1][j-1]+A[i-1][j]+A[i-1][j+1]+A[i][j-1]+A[i][j]+A[i][j+1]+A[i+1][j-1]+A[i+1][j]+A[i+1][j+1];
					sum=sum/9;
					shm->B[i][j]=sum;
					exit(0);
				}
			}
			else
			{
				wait(NULL);
			}
               // *(a+0)=A[i][j];
		//printf(" %d ",*(a+0));

			
               /* while(*(a+1)!=2)
                {
                        ;
                }*/
	}
        }
	printf("The Average matrix is:\n");
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",shm->B[i][j]);
		}
		printf("\n");
	}
        shmdt(shm);
        shmctl(shmid,IPC_RMID,NULL);
        return 0;
}
