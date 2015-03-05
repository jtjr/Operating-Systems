#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

int doFib(int n, int doPrint) {

  int pid1, pid2;
  int status;
  int val;
  val = 0;

  if (n<=1) 
  {
/*
	  if(n == 1)
	  {
		  printf("1,");
	  }
	  else if(n == 0)
	  {
		  printf("0,");
	  }
	  //printf("%d",val);
*/
	  val = n;    // Base case for the recursion
	  return(val);
  }
  else {

    pid1 = fork();

    if (pid1 == 0) {
      exit(doFib(n-1, 1));
    }

    else {              
      waitpid(pid1,&status,0);
      if (WIFEXITED(status))
        val = WEXITSTATUS(status);

      pid2 = fork();

      if (pid2 == 0) {
        exit(doFib(n-2, 0));
      }

      else {
        waitpid(pid2,&status,0);
        if (WIFEXITED(status))
          val += WEXITSTATUS(status);
      }
    }
  }

  if (!doPrint) {
    return(val);
  }
  else if(val <2)
  {
	  //printf("%d,",val);
	  exit(val);
  }
  else
    printf("%d,", val);
    exit(val);
}

int main(){
	int n;//,k;
	printf("Enter the number of a Fibonacci Sequence:\n");
	scanf("%d", &n);
	
	//for( k = n; k >= 0; k--)
	//{
		doFib(n,1);
	//}
    
    
    return 0;
}
