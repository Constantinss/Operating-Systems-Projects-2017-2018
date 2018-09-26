#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {

  //int fd;
  int n = 0;
  int c = 0;
  char *args[1000];
  char arg[100];

  //OPEN FILE DESCRIPTOR
  /*  errno = 0;
    fd = open(argv[1], O_RDONLY);


    if(-1 == fd){
      printf("\n open() failed with error [%s]\n", strerror(errno));
      return 1;
    }
  */

  //SAVE ALL THE ARGUMENTS FROM THE BUFFER
  while (argc - 1 > n) {
    args[n] = argv[n + 1];
    printf("args[%d]: %s\n", n, args[n]);
    n++;
  }

  //READ ALL ARGUMENTS FROM STANDART INPUT
  char ch;
    while (read(STDIN_FILENO, &ch, 1) > 0) {
        if(ch != '\n'){
          printf("char: %c\n", ch);
          arg[c++] = ch;
        }else{
          c = 0;
          args[n++] = arg;
        }
    }

    //SHOW ALL THE ARGUMENTS
    int on = 0;
    while (n > on) {
      printf("args[%d]: %s\n", on, args[on]);
      on++;
    }

    //CLOSE FILE DESCRIPTOR
    //close(fd);

  return 0;
}
