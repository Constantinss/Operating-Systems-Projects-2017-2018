#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char * argv[]){
  int file = 0;
  if(argc <= 0){
    perror("Not loaded file");
  }

  if(argc != 2){
    printf("Type only one file!");
    return -1;
  }

  if((file = open(argv[1],O_RDONLY)) < -1){
    perror("open file");
    return 1;
  }

  char *buffer = (char *) malloc(sizeof(char) * 19);

  if(read(file,buffer,19) != 19) return 1;
  printf("%s\n",buffer);

  if(lseek(file, 10, SEEK_SET) < 0) return 1;

  if(read(file, buffer, 19) != 19) return 1;
  printf("%s\n", buffer);

  return 0;
}
