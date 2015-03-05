#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

int doFib(int n) {

  int pid1, pid2;
  int status;
  int val;
  val = 0;

  if (n<=1) // Base case for the recursion
  {
	  val = n;    
  }
  else {

    pid1 = fork();

    if (pid1 == 0) {
      exit(doFib(n-1));
    }

    else {              
      waitpid(pid1,&status,0);
      val = WEXITSTATUS(status);

      pid2 = fork();

      if (pid2 == 0) {
        exit(doFib(n-2));
      }

      else {
        waitpid(pid2,&status,0);
      
        val += WEXITSTATUS(status);
      }
    }
  }
    return(val);
}

int main(){
	int n,k;
	printf("Enter the number of a Fibonacci Sequence:\n");
	scanf("%d", &n);
	k = n;
	while( k >= 0)
	{

			
			
			printf("\n%d.) %d ",k,doFib(k));
		k--;
	}
    
    
    return 0;
}
