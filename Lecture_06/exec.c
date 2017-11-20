//--------------------------------------------------
//$man wait
//$man execl
//--------------------------------------------------

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	
	printf("System Function Wait Example!\n");
	pid_t pid = fork();

	if(pid < 0){
		perror("fork");

	}else if(pid == 0){
		//sleep(1);
		//execl(*file path, searchpath,location of root, NULL);
		execl("/bin/ls","/bin/ls","/", (char*)0);
		printf("Hello from parent!\n");

	}else{
		printf("Hello from child!\n");
		//waitpid(pid, 0, 0);
	}
 return 0;
}
