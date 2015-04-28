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
void printMatrices();

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
	printf("\n\n");
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
	int i = 0;
	while(i<3){
		sleep(rand() % 3);
		pthread_mutex_lock(&mutex);
		printf("\n\ncustomer %3d\n_________________________\n ", *param);
		int request1 = rand()%resources1;
		int request2 = rand()%resources2;
		int request3 = rand()%resources3;
		//printf("requests %3d %3d %3d\n",request1,request2,request3);
		printMatrices();
		request_resources(param,request1,request2,request3);
		i++;
		pthread_mutex_unlock(&mutex);
	//pthread_exit(0);
	}
	//release_resources(param);
}
int request_resources(int *customer_num, int request1,int request2,int request3){
	
	printf("\n\tCustomer %3d ", *customer_num);
	printf("\n\t\tMax is  %3d  %3d  %3d", maximum[*customer_num][0],maximum[*customer_num][1],maximum[*customer_num][2]);
	printf("\n\t\twants   %3d  %3d  %3d", request1,request2,request3);
	

	need[*customer_num][0] = maximum[*customer_num][0]-allocation[*customer_num][0];
	need[*customer_num][1] = maximum[*customer_num][1]-allocation[*customer_num][1];
	need[*customer_num][2] = maximum[*customer_num][2]-allocation[*customer_num][2];
	printf("\n\t\tneed is %3d  %3d  %3d\n", need[*customer_num][0],need[*customer_num][1],need[*customer_num][2]);
	/*if(need[*customer_num][0] <= available[0] &&need[*customer_num][1] <= available[1] && need[*customer_num][2] <= available[2]){
		printf("\n\n\nBanker grants the resources\n\n\n");
	}
	else
	{
		printf("\n\n\n\n\nfail");
		need[*customer_num][0] = maximum[*customer_num][0]+allocation[*customer_num][0];
		need[*customer_num][1] = maximum[*customer_num][1]+allocation[*customer_num][1];
		need[*customer_num][2] = maximum[*customer_num][2]+allocation[*customer_num][2];
	}
	* */
	
	if(request1 <= available[0] && request2 <= available[0] && request3 <= available[0]){
		if(request1 <= need[*customer_num][0] && request2 <= need[*customer_num][1] && request3 <= need[*customer_num][2]){
			printf("\n\n\nBanker grants the resources\n\n");
			available[0] -= request1;
			available[1] -= request2;
			available[2] -= request3;
			allocation[*customer_num][0] += request1;
			allocation[*customer_num][1] += request2;
			allocation[*customer_num][2] += request3;	
			need[*customer_num][0] -= request1;
			need[*customer_num][1] -= request2;
			need[*customer_num][2] -= request3;
		}
		else{
		printf("\n\n\n***************fail***************\n\n\n");
	}
	}
	else{
		allocation[*customer_num][0] = 0;
		allocation[*customer_num][1] = 0;
		allocation[*customer_num][2] = 0;		
		need[*customer_num][0] = maximum[*customer_num][0]+allocation[*customer_num][0];
		need[*customer_num][1] = maximum[*customer_num][1]+allocation[*customer_num][1];
		need[*customer_num][2] = maximum[*customer_num][2]+allocation[*customer_num][2];
		printf("\n\n\n***************fail***************\n\n\n");
	}
	//exit(0);
}

int release_resources(int *customer_num)
{
	allocation[*customer_num][0] -= need[*customer_num][0];
	allocation[*customer_num][1] -= need[*customer_num][1];
	allocation[*customer_num][2] -= need[*customer_num][2];
	
	need[*customer_num][0] = 0;
	need[*customer_num][1] = 0;
	need[*customer_num][2] = 0;
}

void printMatrices()
{
	int k,m;
	printf("ALLOCATION\n");
	for(k = 0; k < 5; k++)
	{
		for(m = 0; m < 3; m++)
		{
			printf("%2d",allocation[k][m]);
		}
		printf("\n");
	}
	printf("NEED\n");
	for(k = 0; k < 5; k++)
	{
		for(m = 0; m < 3; m++)
		{
			printf("%2d",need[k][m]);
		}
		printf("\n");
	}
	printf("MAX\n");
	for(k = 0; k < 5; k++)
	{
		for(m = 0; m < 3; m++)
		{
			printf("%2d",maximum[k][m]);
		}
		printf("\n");
	}
}

