#include<stdio.h>
#include<string.h>
#include<math.h>
#include<pthread.h>
#include<unistd.h>

#define NUM_OF_DRIVERS 20
#define NUM_OF_CARS 5

pthread_mutex_t mutex[5];


void* driver(void* attr){
		long n = (long)attr;
		for (int m = 0; m < NUM_OF_CARS; ++m)
		{

					pthread_mutex_trylock(&mutex[m]);
					printf("Buyer %ld takes car %d.\n", n, m);
					sleep(1);
					printf("Buyer %ld returns car %d.\n", n, m);		
					pthread_mutex_unlock(&mutex[m]);
		}

	return NULL;
}

int main(){
	pthread_t thread[NUM_OF_DRIVERS];
	long i; 
	for (i = 0; i < NUM_OF_CARS; ++i){
		pthread_mutex_init(&mutex[i], NULL);	
	}
	
	for (i = 0; i < NUM_OF_DRIVERS; i++){
		 pthread_create(&thread[i], NULL, driver, (void*)i);
    }

	for (i = 0; i < NUM_OF_DRIVERS;i++){
		pthread_join(thread[i],NULL);
	}

	for (i = 0; i < NUM_OF_CARS; i++){
		pthread_mutex_destroy(&mutex[i]);
	}
	return 0;
}