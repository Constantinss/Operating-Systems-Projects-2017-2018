//------------------------------------------------------------------------
// NAME: Constantin Mihaylov
// CLASS: XIb
// NUMBER: 13
// PROBLEM: shell
// FILE NAME: shell.c
// FILE PURPOSE:
// write a shell in C
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

char **parse_cmdline(const char *cmdline)
{
	int capacity = 100;
	char **arr = malloc(capacity * sizeof(char*));
	for(int i = 0; i < capacity; ++i){
		arr[i] = malloc(capacity * sizeof(char));
	}

	char string[500];
	strcpy(string, cmdline);

	int position = 0;
	for (char *q = strtok(string," \n"); q != NULL; q = strtok(NULL, " \n")){
		  
		  /* reallocate */
		  int length = strlen(q);
		  if(position == (capacity - 1)|| capacity <= length){
		  	 	capacity *= 2;
		  	   arr = realloc(arr, sizeof(char*) * capacity);
			   for(int i = 0 ; i < capacity; i++)
			   arr[i] = realloc(arr[i], sizeof(char) * capacity);
		  }

		  strcpy(arr[position++], q);
	}
	arr[position] = NULL;
	return arr; 
}

int main(int argc, char const *argv[])
{
	
	char *line, *subcommands;
	size_t bufsize = 100;
	line = (char *)malloc(bufsize * sizeof(char));
	subcommands = (char*)malloc(bufsize * sizeof(char));
	char **commands = NULL, **subcmd;
	while(1){

	write(STDOUT_FILENO, "$ ", 2);
	
	size_t result_cmd = getline(&line,&bufsize,stdin);
		if(result_cmd == -1){
			free(commands);
			break;
		}
			
	char* processtoken = strtok(line ,"|");
        if(processtoken != NULL){
        	
            strncpy(subcommands, (processtoken + strlen(processtoken) + 1), strlen(line));
            processtoken = strtok(NULL, "|");
            subcmd = parse_cmdline(subcommands);
        
       // printf("line: %s", line);

	int pid, status;
	int fd[2];

			commands = parse_cmdline(line);
			pipe(fd);
			    switch(pid = fork()){
				            case -1:
			                    perror("fork");
			                    exit(1);
				            case 0:
				            	
				            	switch(pid = fork()){
				            		case 0: /*child*/
				            		 printf("child\n");
				            		 dup2(fd[0], 0);
				            		 close(fd[1]);
				            		 execv(subcmd[0], subcmd);
				            		 perror(subcmd[0]);
				            		 
				            		default: /*parent*/
				            		 printf("parent\n");
				            		 dup2(fd[1], 1);
				            		 close(fd[0]);
				            		 execv(commands[0], commands);
				            		 perror(commands[0]);

				            		case -1:
				            			perror("fork");
				            			exit(1);
								}
					            	    	     				                    				                                      
				            default:
					            while((pid = wait(&status)) != -1)
					             waitpid(pid, &status, WUNTRACED);
					         	break;				            
				}
		}else{
			if(strchr(commands[0], '\n'))commands[0][strlen(commands[0]) - 1] = '\0';
                   
                    int check = execv(commands[0], commands);
                    if(check == -1)
                    {
                        perror(commands[0]);
                    }  
                       exit(1);
		}					
	}

	free(line);
	free(subcommands);
	return 0;
}


