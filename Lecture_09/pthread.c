#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 5

void *print_hello(void *thread_id){
	int tid;
	tid = (int)thread_id;
	printf("pthread #%d\n", tid);
	pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
	pthread_t threads[NUM_THREADS];
	for (int i = 0; i < NUM_THREADS; i++)
	{
		printf("In main: creating thread %d\n", i );
		int rc = pthread_create(&threads[i], NULL, print_hello, (void *) i);
		if(rc){
			printf("ERROR: pthread create() return %d\n", rc);
			exit(-1);
		}
	}

	printf("MAIN going to exit ...\n");
	pthread_exit(NULL);
	return 0;
}