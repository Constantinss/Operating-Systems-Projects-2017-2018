#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(int argc, char const *argv[]) {

  char ch; //reading bytes
  int fd = 0; //file descriptor
  char prev; //previous byte
  int statements_n = 0; //count
  int words_n = 0; //count
  int status; //wait pid status


    for (size_t i = 1; i < argc; i++) {
      pid_t pid = fork();

      if(pid == 0){
          //CHILD

            fd = open(argv[i], O_RDONLY);

            if(fd == -1){
              perror("open");
              exit(-1);
            }

            statements_n = 0; //count
            words_n = 0; //count

            while(read(fd, &ch, 1) != 0){
              if(ch == '.' || ch =='!' || ch == '?' || ch == ','){

                if(prev != '.'){
                  statements_n++;
                }
              }
              if(ch == ' '){
                if(prev != ' '){
                  words_n++;
                }
              }
              prev = ch;
            }

            printf("file name: %s \tstatements: %d \twords: %d\n", argv[i], statements_n, words_n);

       exit(1);
     }else if(pid < 0){
       perror("fork");
       exit(-1);
     }

    }

    for (size_t y = 1; y < argc; y++) {
      pid_t pid_w;
      if((pid_w = wait(&status)) < 0){
        perror("wait");
      }
    }

  return 0;
}
