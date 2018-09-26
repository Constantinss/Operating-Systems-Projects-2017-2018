#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {

  int fd; //file descriptor
  char ch; //read bytes
  char prev = '\0'; //previous elem
  int statems;
  int words;
  int status;


    for (size_t x = 1; x < argc; x++) {

      pid_t pid = fork();

      if(pid == 0){
        /*CHILD*/

        fd = open(argv[x], O_RDONLY);

        if(fd < 0){
          perror("open");
          exit(1);
        }
        statems = 0;
        words = 0;
        while ((read(fd, &ch, 1)) != 0) {
          if(ch == '.' || ch == ',' || ch == '?' || ch == '!'){
            if(prev != '.'){
              statems++;
            }
          }
          if(ch == ' '){
            if(prev != ' '){
              words++;
            }
          }
          prev = ch;
        }

       printf("%s %d %d\n", argv[x], words, statems);
       exit(1);
     }else if(pid < 0){
       perror("fork");
       exit(-1);
     }
    }

    pid_t pid_w;
    for (size_t y = 1; y < argc; y++) {
      if((pid_w = wait(&status)) < 0){
        perror("wait");
        exit(-1);
      }
    }

  return 0;
}
