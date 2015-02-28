#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

void doFib(int n, int doPrint)
{
    int status;
    int print;
    pid_t pid1;
    pid_t pid2;
    int sum1 = 0;
    int sum2 = 0;

    if (n < 2)
        exit(n);

    pid1 = fork();

    if (pid1 == 0)
    {
        doFib(n-1, doPrint);
        exit(n-1);
    }

    pid2 = fork();

    if (pid2 == 0)
    {
        doFib(n-2, doPrint);
        exit(n-2);
    }
    
    if(pid1 > 0)
    {
		waitpid(pid1,&status,0);
		if(WIFEXITED(status))
		{
			sum1 = WEXITSTATUS(status);
		}
	}
	
	if(pid2 > 0)
    {
		waitpid(pid2,&status,0);
		if(WIFEXITED(status))
		{
			sum2 = WEXITSTATUS(status);
		}
	}
    print = sum1 + sum2;

    if(doPrint)
        printf("%d,", print);
    else
        exit(0);
}
int main(){
	int n;
	printf("Enter the number of a Fibonacci Sequence:\n");
	scanf("%d", &n);
	doFib(n,1);
    	return 0;
}
