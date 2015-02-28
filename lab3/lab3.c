#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int doFib(int n, int doPrint)
{
    int status;
    int print;
    pid_t pid1;
    pid_t pid2;
    int sum1 = 0;
    int sum2 = 0;

    if (n < 2)
        return(n);

    pid1 = fork();

    if (pid1 == 0)
    {
        
        exit(doFib(n-1, 1));
    }

    pid2 = fork();

    if (pid2 == 0)
    {
        
        exit(doFib(n-2, 1));
    }
    
    if(pid1 > 0)
    {
		waitpid(pid1,&status,0);
		if(WIFEXITED(status))
		{
			sum1 += WEXITSTATUS(status);
		}
	}
	
	if(pid2 > 0)
    {
		waitpid(pid2,&status,0);
		if(WIFEXITED(status))
		{
			sum2 += WEXITSTATUS(status);
		}
	}
    print = sum1 + sum2;

    if(doPrint)
    {
        printf("%d,", print);
        return print;
    }
    else
	{
		return 0;
	}
}
int main(){
	int n;
	printf("Enter the number of a Fibonacci Sequence:\n");
	scanf("%d", &n);
	doFib(n,1);
    return 0;
}
