#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int doFib(int n)
{
	if(n == 0)
	{
		return (0);
	}
	else if(n == 1)
	{
		return (1);
	}
	else if(n > 1)
	{
		//return (doFib(n-1)+doFib(n-2));
	}
	pid_t pid1 = fork();
	if(pid1 == 0)
	{
		exit(doFib(n-1));
	}
	pid_t pid2 = fork();
	if(pid2 == 0)
	{
		exit(doFib(n-2));
	}
   	 else 
    	{
		int status1;
		int status2;
		waitpid(pid1,&status1,0);
        	waitpid(pid2, &status2, 0);
        	printf("Parent ends %d", (WEXITSTATUS(status1) + WEXITSTATUS(status2)));
    	}
}
int main(){
	int n;
	printf("Enter the number of a Fibonacci Sequence:\n");
	scanf("%d", &n);
	doFib(n);
    	return 0;
}
