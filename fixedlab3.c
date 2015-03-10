/* CECS 326 
 * Russell Tan
 * Jose Terrones Jr.
 * 3/09/2015
 * 
 */
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <ctype.h> 
#include <sys/wait.h> 
//Definition of fibonacci function
int doFib(int n); 

int main()
{
	int val,i,k;
	printf("Enter the number of a Fibonacci Sequence:\n");
	scanf("%d", &i);
	
	printf("\n-------------\n");

	for(k = 0; k <= i; k++)
	{
		val = doFib(k);
		printf("%d.)   %d\n",k,val);
	}
	
	printf("-------------\n");
    exit(0);
}

int doFib(int n) 
{
    pid_t pid1;
    pid_t pid2;
    int status1;
    int status2; 
    
    //Base case for recursion
    if( n < 2 )
	    return(n);
    
    //Create left branch
    pid1 = fork();
	
    if (pid1 == 0) 
	    exit(doFib(n-1));
    
    //Create right branch
    pid2 = fork();

    if (pid2 == 0) 
	    exit(doFib(n-2));
  
	//Assign return values for when the children finish
    (void)waitpid(pid1,&status1,0);
    (void)waitpid(pid2,&status2,0);
	
	//Return the sum
    return (WEXITSTATUS(status1)+WEXITSTATUS(status2));
}
