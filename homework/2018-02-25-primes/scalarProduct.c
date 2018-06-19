#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_TREADS 5

int N = 1000000;
double *v, *w; 

void* dot(void* a){
	long arg = atol(a);
	//printf("pthread: %ld\n", arg);
	
	double sum = 0;

	for (long i = 1; i < arg; ++i){
		sum += v[i]*w[i];
		printf("Show: %f\n", sum); 	
	}
 
 pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
	pthread_t thread[NUM_TREADS];
	int chunk = N / NUM_TREADS;

	v = (double*)malloc(chunk * sizeof(double));
	w = (double*)malloc(chunk * sizeof(double));
	for (int i = 0; i < chunk; ++i){
		v[i] = i*2;
		w[i] = i*3;
	}

	for (int t = 0; t < NUM_TREADS; ++t)
	{
		//printf("%s\n", argv[1]);
		//printf("%d\n", atoi(argv[1]));
		pthread_create(&thread[t], NULL, dot, (void *)argv[1]);
	}
	
	for (int t = 0; t < NUM_TREADS; ++t)
	{
		pthread_join(thread[t],NULL);
	}

	pthread_exit(NULL);
	return 0;
}