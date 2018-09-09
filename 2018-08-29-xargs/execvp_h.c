#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

  int main(int argc, char * const argv[])
  {
     pid_t pid;
     //char *const parmList[] = {"/bin/ls", "-l", "/u/userid/dirname", NULL};

     if ((pid = fork()) == -1)
        perror("fork() error");
     else if (pid == 0) {
        execvp("ls", argv);
        printf("Return not expected. Must be an execvp() error.n");
     }

      if(pid > 0){
        //parent
        wait(0);
        //printf("parent\n");
      } 
      
     return 0;
  }
