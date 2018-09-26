#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//OPEN & FORK
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//WAIT
#include <sys/wait.h>



int main(int argc, char const *argv[]) {

  int status; //wait status
  int words_n; //words count
  int statements_n; //statements count
  int fd;  //file descriptor
  char ch; //reading bytes
  char prev; //reading previous byte

  //CREATE A FEW PROCESS
  for (size_t i = 1; i < argc; i++) {

      pid_t pid = fork();

      if(pid == 0){
          //OPEN FILE
          fd = open(argv[i], O_RDONLY);
          if(fd < 0){
            perror("open");
            exit(-1);
          }

          //READ INFORMATION FROM THE OPENED FILE
          words_n = 0;
          statements_n = 0;
          while(read(fd, &ch, 1) != 0){
              if(ch == '.' || ch == '!' || ch == '?' || ch == ','){
                if(prev != '.')
                statements_n++;
              }
              if(ch == ' '){
                if(prev != ' ')
                words_n++;
              }
              prev = ch;
          }

          //SHOW THE INFORMATION
          printf("%s\t%d\t%d\n", argv[i], statements_n, words_n);
          exit(1);
      }else if(pid < 0){
        perror("fork");
        exit(-1);
      }
  }

  //WAIT PROCESS TO END
  pid_t pid_w;
  for (size_t i = 1; i < argc; i++) {
    if((pid_w = wait(&status)) < 0){
      perror("wait");
      exit(-1);
    }
  }

  return 0;
}
