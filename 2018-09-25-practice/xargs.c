#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

  char ch; //reading bytes
  int c = 0; //counter for reading line
  int n = 0; //counter for copying arguments
  int num = 0; //counter for showing arguments
  //char line[1000];
  //char *args[1000];
  char args[1000][1000];

  //COPY THE ARGUMENTS FROM THE BUFFER
    while (argc > n + 1) {
      strcpy(args[n],argv[n + 1]);
      n++;
    }

  //READ FROM STANDART INPUT WHILE CTRL + D
  //it is not working, couse the args[0] -> line && args[1] -> line ...
  //that is not the way it works in c programming
    while(read(STDIN_FILENO, &ch, 1) > 0){
      if(ch != '\n'){
        //line[c++] = ch;
        args[n][c++] = ch;
      }else{
        //line[c] = 0x00;
        //line[c] = '\0';
        args[n][c] = '\0';
        c = 0;
        printf("args: %s\n", args[n] );
        n++;
      }
    }

  //SHOW ALL ARGUMENTS IN THE LIST
    printf("\n----------------\n");
    printf(" SHOW ARGUMENTS\n" );
    while (n > num) {
      printf("args: %s\n", args[num]);
      num++;
    }

  //RUN EXECVP
  printf("\n----------------\n");
  printf(" EXECVP & EXECV ARGUMENTS\n" );
    char *a[] = { "ls", "-l", 0 };
    execvp(a[0], a);
    execv("/bin/ls", a);

  //RUN FORK
    printf("\n----------------\n");
    printf(" FORK ARGUMENTS\n" );
    pid_t pid, c_pid;
    int status;

    char *ar[] = { "/bin/ls", "-l", 0 };


    c_pid = fork();
    if(c_pid == 0){
      /*CHILD*/

      execvp(ar[1], ar);
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

  return 0;
}
