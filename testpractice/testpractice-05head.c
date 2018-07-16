#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

int catFile(const char * fileName){
  int lines = 1;
  int i = 0;
  char rchar;
  char buffer[1000];
  ssize_t read_bytes, write_result;
  int cresult;
  //ssize_t written = 0;

  int fd = open(fileName, O_RDONLY);
  if(fd < 0){
    perror("ERR: open_");
    return 1;
  }

  while(lines != 10){
    read_bytes = read(fd, &rchar, 1);
    if(rchar == '\n')lines++;

    if( read_bytes < 0){
      perror("ERR: read_");
      return 2;
    }else if( read_bytes == 0){
      break;
    }
    buffer[i++] = rchar;
  }

  write_result = write(STDOUT_FILENO, buffer, i);
  if(write_result < 0){
    perror("ERR: write_");
    return 3;
  }

  cresult = close(fd);
  if(cresult < 0){
    perror("ERR: close_");
    return 4;
  }
  return 0;
}

int main(int argc, char * argv[]){

  for(int i = 1; i < argc; ++i )
    catFile(argv[i]);

  return 0;
}
