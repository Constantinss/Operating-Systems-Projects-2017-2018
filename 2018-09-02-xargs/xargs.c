#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){

	int status;
	char * args[1000];
	char  str[1000];
	//int count = argc;
	pid_t pid, w_pid;
	int n = 0;
	while(argc > n){
		args[n] = argv[n];
		n++;
	}
	//printf("%s\n", args[n-1]);
		

	
		scanf("%s", str);
		args[n] = str;
		
	
	//args[n] = NULL;
	

	

/*
	int n = 1;
	while(argc > n)
		printf("%s ", argv[n++]);	

	int a = 0;
	while( count > a + 1){
		printf("%s ", args[a]);
		a++;	
	}
		printf("%s\n", args[a]);
*/
    int a = 0;

	while (n >= a ){
		printf("%s\n", args[a]);
		a++;
	}
	printf("-------------------------\n");

	pid = fork();
	
	if(pid == 0){
		//CHILD
		printf("child \n");
		execvp(args[1], args);

		perror("execvp failed.");
	}else if(pid > 0){
		//PARENT

		if((w_pid = wait(&status)) < 0){
			perror("parent failed.");
			exit(1);
		}
	}else{
		perror("fork failed.");
		exit(1);
	}

	return 0;
}