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
	int arg = 0;
	int error = 0;
	
	for(int i = 0; i < atoi(argv[1]) && error == 0; ++i){
		char string[30] = "";
		pid_t pid = fork();
		if(pid < 0){
			perror(argv[2]);
			exit(-1);
		}else if(pid == 0){
			if(argv[3] != NULL)
				execl(argv[2],argv[2], argv[3], (char*)0 );
			else
			arg = execl(argv[2],argv[2], "/", (char*)0 );
			
			if(arg < 0){
				error = 1;
				strcat(string, argv[0]);
				strcat(string, ": ");
				strcat(string, argv[2]);
				perror(string);
				exit(-1);
			}else if(arg == 0){
				error = 1;
				strcat(string, argv[0]);
				strcat(string, ": ");
				strcat(string, argv[2]);
				perror(string);
				exit(-1);
			}

			
			//printf("Hello from child!\n");
		}else{
			//printf("Hello from parent!\n");
			waitpid(pid, 0 ,0);
		}
	}
 return 0;
}
