#include<stdio.h>
#include<math.h>
#include<pthread.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>

#define SIZE 20

int total;
pthread_mutex_t mutex;
int miner_th = 1;
int trader_th = 1;

void* sum_miner(void* attr){
	int i;
	int j = 1;
		for(i = 0; i < *(int*)attr; i++)
		{
			pthread_mutex_lock(&mutex);
				total += 10;
			pthread_mutex_unlock(&mutex);
			if(j > miner_th)j = 1;
			printf("Miner %d gathered 10 gold\n",j++ );
		}
	sleep(2);
	return NULL;
}

void* sum_trader(void* attr){
	int i;
	int j = 1;
	int count = 0;
	int miner = miner_th;

	pthread_mutex_lock(&mutex);
		for(i = 0; i < *(int*)attr; i++)
		{	if(count == trader_th){
				miner = miner_th;
				count = 0;
			}
			if( miner-- ){
				total -= 10;

				if(j > miner_th)j = 1;
			 printf("Trader %d sold 10 gold\n",j++ );
			}else{
			 printf("The warehouse is empty, cannot sell!\n");
			}
			count++;
		}
	pthread_mutex_unlock(&mutex);
    sleep(2);
	return NULL;
}



int main(int argc, char* argv[]){
	pthread_t thread_miner[SIZE];
	pthread_t thread_trader[SIZE]; 
	pthread_mutex_init(&mutex, NULL);
	int i;

			if(argc > 1){
				miner_th = atoi(argv[1]);
				trader_th = atoi(argv[2]);
			}

			for(int i = 0; i < SIZE; i++){
				pthread_create(&thread_miner[i], NULL, sum_miner, &miner_th);
				
				pthread_join(thread_miner[i],NULL);
	
				pthread_create(&thread_trader[i], NULL, sum_trader, &trader_th);
				
				pthread_join(thread_trader[i],NULL);
			}
			
		printf("Gold: %d\n", total);
		pthread_mutex_destroy(&mutex);
	return 0;
}