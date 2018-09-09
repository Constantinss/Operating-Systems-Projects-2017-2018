#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>


int RemainingMoney = 10000;
pthread_mutex_t mutex;



void * withdraw(void * arg){
	int t1 = 0;
	while(t1 < 20)
	{
		pthread_mutex_lock(&mutex);
		if(RemainingMoney >= 50){
		RemainingMoney -= 50;
		printf("Banker %ld withdraw $50 to the bank account\n", ((long)arg) + 1);
		//sleep(2);
		}else if(RemainingMoney <= 0) {

			 pthread_mutex_unlock(&mutex);
			 pthread_exit(NULL);
		}
		pthread_mutex_unlock(&mutex);
		t1++;
	}

 pthread_exit(NULL);
}


void * deposited(void * arg){
	int t2 = 0;
	while(t2 < 20)
	{
		pthread_mutex_lock(&mutex);
		if(RemainingMoney > 0){
		RemainingMoney += 50;
		printf("Banker %ld deposited $50 to the bank account\n", ((long)arg) + 1);
		//sleep(2);
		}else{
			pthread_mutex_unlock(&mutex);
			pthread_exit(NULL);
		}
		t2++;
		pthread_mutex_unlock(&mutex);
	}

 pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
	long withdraw_attr = 1;
	long deposited_attr = 1;
	
	if(argc >= 2 && atoi(argv[1]) >= 1 && atoi(argv[2]) >= 1){
		withdraw_attr = atoi(argv[1]);
		deposited_attr = atoi(argv[2]);
	}


	pthread_t withdraw_t[1000];
	pthread_t deposited_t[1000];
	pthread_mutex_init(&mutex,NULL);

	for (long i = 0; i < withdraw_attr; ++i)
	{
		pthread_create(&withdraw_t[i], NULL, &withdraw, (void*)i);
	}
	for (long i = 0; i < deposited_attr; ++i)
	{
		pthread_create(&deposited_t[i], NULL, &deposited, (void*)i);
	}
	for (long i = 0; i < withdraw_attr; ++i)
	{
		pthread_join(withdraw_t[i], NULL);
	}
	for (long i = 0; i < deposited_attr; ++i)
	{
		pthread_join(deposited_t[i], NULL);
	}
	
	pthread_mutex_destroy(&mutex);
	if (RemainingMoney > 0)
		printf("Remaining money: %d\n", RemainingMoney);
	else
		printf("BANKRUPT!\n");
	return 0;
}