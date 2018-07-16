#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int catFile(const char * file){
  int lines = 1;
  char rchar;
  char buffer[1000];
  ssize_t read_bytes, write_bytes;
  int close_file;
  int counter = 0;

  int fd = open(file, O_RDONLY);
  if(fd < 0){
    perror("ERR: open_");
    return 2;
  }

  while(lines != 10){
    read_bytes = read(fd, &rchar, 1);
    if(rchar == '\n')lines++;

    if(read_bytes < 0){
      perror("ERR: read_");
      return 3;
    }else if(read_bytes == 0){
      break;
    }
    buffer[counter++] = rchar;
  }

  write_bytes = write(STDOUT_FILENO, buffer, counter);
  if(write_bytes < 0){
    perror("ERR: write_");
    return 4;
  }

  close_file = close(fd);
  if(fd < 0){
    perror("ERR close_");
    return 5;
  }
  return 1;
}

int main(int argc, char * argv[]){

  for(int i = 1; i < argc; i++ )
    catFile(argv[i]);
  return 0;
}
