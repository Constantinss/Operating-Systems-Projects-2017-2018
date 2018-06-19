#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_THREADS 5

void *print_hello(void *thread_id){
	int tid;
	tid = (int)thread_id;
	printf("Hello World! It's me, thread #%d!\n", tid);
}

int main(int argc, char const *argv[])
{
	pthread_t t[NUM_THREADS];
	for (int i = 0; i < NUM_THREADS; ++i)
	{ 
		int rc = pthread_create(&t[i], NULL, print_hello, (void *)i);
		if(rc){
			printf("ERROR: pthread_Create() return %d\n", rc);
			exit(-1);
		}
	}

	for (int i = 0; i < NUM_THREADS; ++i)
	{
		void * status;
		pthread_join(t[i], (void **)&status);
	}
	printf("MAIN is going to exit...\n");
	pthread_exit(NULL);
	return 0;
}