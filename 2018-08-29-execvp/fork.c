#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char * const argv[])
{
	
	pid_t pid  = fork();

	if(pid == -1){
		perror("fork failed.");
		exit(1);
	}	
	if(pid == 0){
		// child now exec's
		// printf("child\n");
		char* args[] = {"./bogosort", "1", "2", "3", NULL};

		if( execv (args[0], args) == -1){
			perror("execvp");
		}
	}
	if(pid > 0){
		//parent
		wait(0);
		printf("parent\n");
	}
	return 0;
}