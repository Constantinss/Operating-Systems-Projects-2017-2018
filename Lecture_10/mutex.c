#include<stdio.h>
#include<math.h>
#include<pthread.h>

#define NUM_OF_THREADS 2
#define ARRAY_SIZE 1000

double total;
pthread_mutex_t mutex;

void* sum(void* attr){
	int i;
	// Don't put here lock, because the program will use only one thread
	for(i = 0; i < ARRAY_SIZE / NUM_OF_THREADS; i++)
	{
		// sync my signals
		// lock and unlock are slower operations. Use as less as possible.  
		pthread_mutex_lock(&mutex);
		// takes more time 
		total += sin(i) * sin(i) + cos(i) * cos(i);
	
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main(){
	pthread_t thread[NUM_OF_THREADS]; 
	pthread_mutex_init(&mutex, NULL);

	int i;
	for(int i = 0; i < NUM_OF_THREADS; i++){
		pthread_create(&thread[i], NULL, sum, NULL);
	}
	for(i = 0; i < NUM_OF_THREADS;i++){
		pthread_join(thread[i],NULL);
	}
	printf("SUM = %f\n", total);
	pthread_mutex_destroy(&mutex);
	return 0;
}