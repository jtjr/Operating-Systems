/* Lab 4 - pthreads
 * 
 * Jose Terrones Jr. 
 * ID: 010178556
 * 
 * Russell Tan
 * ID: 011529945
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//Global Variables
int n = 0;
int randA[0];
int avg = 0;
int min = 0;
int max = 0;

//Instantiate the methods
void *getAvg(void *ptr);
void *getMax(void *ptr);
void *getMin(void *ptr);

//Main method
int main(int argc, char *argv[])
{
	//Instantiate the pthread's
	pthread_t thread1, thread2, thread3;
	
	//Ensure that random vars are random every run
	srand(time(NULL));
	
	//Size of array is first terminal argument
	n = atoi(argv[1]);
	//Instantitate an array of size n
	randA[n];
	
	int  i = 0;
	printf("\n\n\n\n");
	
	//Fill array with n random numbers from [-100,100]
	for(i = 0; i < n; i++){
		randA[i] = rand()%201-100;
		printf("%d ",randA[i]);
	}
	
	//Create the threads
	pthread_create(&thread1, NULL, (void *)getAvg, (void *) &randA);
	pthread_create(&thread2, NULL, (void *)getMax, (void *) &randA);
	pthread_create(&thread3, NULL, (void *)getMin, (void *) &randA);
	
	//Join the threads, Parent waits for exit()
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	pthread_join(thread3,NULL);
	
	//Print results from global results
	printf("\n\n\tThe average value is = %3d\n",avg);
	printf("\tThe maximum value is = %3d\n",max);
	printf("\tThe minimum value is = %3d\n\n",min);
	printf("\n\n\n\n");
	return 0;
}

//Get average 
void *getAvg(void *ptr){
	int i;
	int sum = 0;
	for(i = 0; i < n; i++)
		sum += randA[i];

	avg = sum / n;
	pthread_exit(0);
}

//Get max by comparison
void *getMax(void *ptr){
	int i;
	for(i = 0; i < n; i++)
		if( randA[i]> max )
			max = randA[i];
		
	pthread_exit(0);
}

//Get min by comparison
void *getMin(void *ptr){
	int i;
	for(i = 0; i < n; i++)
		if( randA[i]< min )
			min = randA[i];
		
	pthread_exit(0);
}
