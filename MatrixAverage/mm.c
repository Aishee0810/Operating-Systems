#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<signal.h>
#include<sys/wait.h>
#include<errno.h>
#include<string.h>

typedef struct matrix
{
   int B[4][4];
}matrix;

int main()
{
  int A[4][4];
  matrix *shm;
  int shmid,i,j,k,l,d,c=1,m,n;
  printf("Enter threshold value:");
  scanf("%d",&d);
  printf("Enter number of rows:");
  scanf("%d",&m);
  printf("Enter number of columns:");
  scanf("%d",&n);
  if((shmid = shmget(IPC_PRIVATE,100,IPC_CREAT|0666)) < 0)
  {
    perror("ERROR!!");
    exit(0);
  }
  if((shm = (matrix *)shmat(shmid,NULL,0)) == (matrix *) -1)
  {
    perror("ERROR!!");
    exit(0);
  }
  for(i=0;i<m;i++)
  {
    for(j=0;j<n;j++)
    {
       printf("A[%d][%d] = ",i,j);
       scanf("%d",&A[i][j]);
    }   
  }
  printf("Actual Matrix:\n");
  for(i=0;i<m;i++)
  {
    for(j=0;j<n;j++)
    {
      printf("%d ",A[i][j]);
    }
    printf("\n");
  }
  while(1)
  {
    for(i=0;i<m;i++)
    {
      for(j=0;j<n;j++)
      {
        if(fork()==0)
      {
        int sum;
      //  shmid = shmget(key,SHMSIZE, IPC_CREAT | 0666);
            //  shm = shmat(shmid,NULL,0);
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
         
      }
    }
    int max=shm->B[0][0],min=shm->B[0][0];
    for(i=0;i<m;i++)
    {
      for(j=0;j<n;j++)
      {
        if(shm->B[i][j] > max)
          max = shm->B[i][j];
        else if(shm->B[i][j] < min)
          min = shm->B[i][j];
      }
    }
    if((max-min) < d)
    {
      shmdt(shm);
      shmctl(shmid,IPC_RMID,NULL);
      exit(0);
    }
    printf("The average matrix is %d:\n",c);
    c++;
    for(i=0;i<m;i++)
    {
      for(j=0;j<n;j++)
      {
        printf("%d ",shm->B[i][j]);
        A[i][j] = shm->B[i][j];
      }
      printf("\n");
    }
    
  }

  return 0;
}
