#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

void initialize_allocation();
int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int resources1;
int resources2;
int resources3;
pthread_mutex_t mutex;
void *customer(int *param);

int main(int argc, char *argv[]){
	srand (time(NULL));
	int k;
	if(argc < 3){
		printf("\n Error\n");
		exit(1);
	}
	else{
		resources1 = atoi(argv[1]);
		resources2 = atoi(argv[2]);
		resources3 = atoi(argv[3]);
	}
	initialize_allocation();
	pthread_t customers[NUMBER_OF_CUSTOMERS];
	for(k=0;k<5;k++){
		printf("Creating customer thread #%3d\n", k);
		maximum[k][0] = rand()%resources1;
		maximum[k][1] = rand()%resources2;
		maximum[k][2] = rand()%resources3;
		printf("Maximum %3d %3d %3d \n",maximum[k][0],maximum[k][1],maximum[k][2]);
	}
	int i,j,z,l,a;
	i=0;j=1;z=2;l=3;a=4;
	pthread_create(&customers[0],NULL,(void *)customer,(int *)&i);
	pthread_create(&customers[1],NULL,(void *)customer,(int *)&j);
	pthread_create(&customers[2],NULL,(void *)customer,(int *)&z);
	pthread_create(&customers[3],NULL,(void *)customer,(int *)&l);
	pthread_create(&customers[4],NULL,(void *)customer,(int *)&a);
	sleep(5);
	exit(0);
}

void initialize_allocation(){
	available[0] = resources1;
	available[1] = resources2;
	available[2] = resources3;
}

void *customer(int *param){
	sleep(rand() % 3);
	pthread_mutex_lock(&mutex);
	printf("customer %3d ", *param);
	int request1 = rand()%resources1;
	int request2 = rand()%resources2;
	int request3 = rand()%resources3;
	printf("requests %3d %3d %3d\n",request1,request2,request3);
	if(request1 <= resources1 && request2 <= resources2 && request3 <= resources3)
	{
		printf("works\n");
		allocation[*param][0]=request1;
		allocation[*param][1]=request2;
		allocation[*param][2]=request3;
	}
	sleep(1);
	pthread_mutex_unlock(&mutex);
	//pthread_exit(0);
}

