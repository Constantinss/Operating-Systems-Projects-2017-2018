#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]){
  pid_t cpid, w;
  int wstatus;

  cpid = fork();
  if(cpid == -1){
    perror("fork");
    exit(EXIT_FAILURE);
  }

  /* core executed by child*/
  if(cpid == 0){
    printf("Child PID is %ld\n", (long) getpid());
    if(argc == 1){
      pause();
      /*wait for signals*/
      _exit(atoi(argv[1]));
    }else{
      /*core executed by parent*/
      do{
        w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
        if(w == -1){
          perror("waitpid");
          exit(EXIT_FAILURE);
        }

        if(WIFEXITED(wstatus)){
          printf("exited, status=%d\n", WEXITSTATUS(wstatus));
        }else if(WIFSIGNALED(wstatus)){
          printf("killed by signal %d\n", WTERMSIG(wstatus));
        }else if(WIFSTOPPED(wstatus)){
          printf("stopped by signal %d\n", WSTOPSIG(wstatus));
        }else if(WIFCONTINUED(wstatus)){
          printf("continue\n");
        }
      }while(!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
      exit(EXIT_SUCCESS);
    }
  }
}
