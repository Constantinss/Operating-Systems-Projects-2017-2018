#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	printf("helloExec.c \n");
	printf("	My PID: %d \n", getpid());

	printf("	My arguments: ");
	for(int i = 0; i < argc; i++){
		printf("%s \n", argv[i]);
	}

	printf("\n");

	return 0;
}