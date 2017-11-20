//------------------------------------
// $./a.out 4 /bin/ls
// $ man 3 execv 
// $ man 2 waitpid
//------------------------------------
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
	for(int i = 0; i < atoi(argv[1]); ++i){
		pid_t pid = fork();
		if(pid < 0){
			perror("fork");
		}else if(pid == 0){
			execl(argv[2],argv[2], "/", (char*)0 );
			//printf("Hello from child!\n");
		}else{
			//printf("Hello from parent!\n");
			waitpid(pid, 0 ,0);
		}
	}
 return 0;
}
