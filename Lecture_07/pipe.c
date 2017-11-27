#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
	int fildes[2];
	char * message = "Hello world!";
	char buffer[256];
	
	if(pipe(fildes)){
		perror("pipe");
	}
	
	pid_t pid = fork();
	if(pid < 0){
			perror("fork");
	}else if(pid == 0){
			printf("child\n");
			// close(fildes[0]);
			// write(fildes[1], message, strlen(message) + 1);
			
			dup2(0, fildes[0]);// copy out of pipe with in execl
			execlp("wc","wc", NULL);
			
	}else{
	
			waitpid(pid, 0, 0);
			printf("parent\n");
			//close(fildes[1]);
			//read(fildes[0], buffer,sizeof(buffer));
			//printf("Message %s\n", buffer);

	}
 return 0;
}
// ls -l
// ls | wc information about 'in' pipe
// ps || wc 'in' pipe cp processes of ps
