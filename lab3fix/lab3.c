#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <ctype.h> 
#include <sys/wait.h> 

int doFib(int n); 

int main()
{
	int val,i,k;
	printf("Enter the number of a Fibonacci Sequence:\n");
	scanf("%d", &i);

	for(k = 0; k <= i; k++)
	{
		val = doFib(k);
		printf("%d\n",val);
	}
    exit(0);
}

int doFib(int n) 
{

  pid_t pid1;
  pid_t pid2;

  if( n < 2 )
	return(n);
  
  
  pid1 = fork();

  if (pid1 == 0) 
	exit(doFib(n-1));
  
  
  int status1;
  int status2; 
   
  pid2 = fork();

  if (pid2 == 0) 
	exit(doFib(n-2));
  
  
  (void)waitpid(pid1,&status1,0);
  (void)waitpid(pid2,&status2,0);

  return (WEXITSTATUS(status1)+WEXITSTATUS(status2));
}
