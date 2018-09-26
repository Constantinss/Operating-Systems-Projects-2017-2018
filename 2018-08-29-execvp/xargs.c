#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	//arguments for ls, will run: ls -l /bin
	//char * args[100] = {"ls", "-l", ".", "../../", NULL};
	pid_t pid, c_pid;
	int status;

	c_pid = fork();

	if(c_pid == 0){
		/*CHILD*/

		//execute ls
		execvp(argv[1], argv);

		perror("execvp failed");
	}else if(c_pid > 0){
		/*PARENT*/

		if((pid = wait(&status)) < 0){
			perror("wait failed");
			exit(1);
		}

	}else{
		perror("fork failed");
		exit(1);
	}
	//execvp(argv[0], argv);


	return 0;
}