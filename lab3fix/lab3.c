#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int doFib(int n); 

int main(){
	int val,n,k;
	printf("Enter the number of a Fibonacci Sequence:\n");
	scanf("%d", &n);
	k = n;
	val = 0;
	for(k = 0; k <= n; k++)
	{
		val = doFib(k);
		printf("\n %d ",val);
	}
    exit(0);
}
int doFib(int n) 
{

  pid_t pid1, pid2;

  if(n == 1)
  {
	  return 1;
  }
  else if(n == 0)
  {
	  return 0;
  }
  /*
  if( n < 2 )
  {
	  return(n);
  }
  */
  pid1 = fork();

  if (pid1 == 0) 
  {
     exit(doFib(n-1));
  }
  
  int status1,status2;  
  pid2 = fork();

  if (pid2 == 0) 
  {
	exit(doFib(n-2));
  }
  
  (void)waitpid(pid1,&status1,0);
  (void)waitpid(pid2,&status2,0);

  return(WEXITSTATUS(status1)+WEXITSTATUS(status2));
}
