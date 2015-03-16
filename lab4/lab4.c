#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int n = 0;
int randA[0];
int avg = 0;
int min = 0;
int max = 0;

void *avg1(void *ptr);
void *maxsum(void *ptr);
void *minsum(void *ptr);

int main(int argc, char *argv[])
{
	n = atoi(argv[1]);
	randA[n];
	int  i = 0;
	for(i = 0; i < n; i++){
		randA[i] = rand()%201-100;
		printf("%d: %d\n",(i+1),randA[i]);
	}
	pthread_t thread1, thread2, thread3;
	pthread_create(&thread1, NULL, (void *)avg1, (void *) &randA);
	pthread_create(&thread2, NULL, (void *)maxsum, (void *) &randA);
	pthread_create(&thread3, NULL, (void *)minsum, (void *) &randA);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	pthread_join(thread3,NULL);
	printf("avg = %d\n",avg);
	printf("max = %d\n",max);
	printf("min = %d\n",min);
	return 0;

}

void *avg1(void *ptr){
	//printf("Hello from the new thread!\n");
	int i;
	int sum = 0;
	for(i = 0; i < n; i++)
		sum += randA[i];


	avg = sum / n;
	pthread_exit(0);
}
void *maxsum(void *ptr){
	int i;
	int temp = 0;
	for(i = 0; i < n; i++)
		if( randA[i]> max )
			max = randA[i];
		
	pthread_exit(0);
}
void *minsum(void *ptr){
	int i;
	int temp = 0;
	for(i = 0; i < n; i++)
		if( randA[i]< min )
			min = randA[i];
		
	pthread_exit(0);
}