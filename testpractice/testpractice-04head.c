#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int catFile(const char* file){
  char buff[10000];
  int i = 0;
  int fd = open(file, O_RDONLY);
  int cresult;
  int lines = 1;
  char rchar;
  ssize_t read_bytes, wresult;
  ssize_t written = 0;

  if( fd < 0){
    perror( "ERR: open_ ");
    return 1;
  }

  while(lines != 10){
    read_bytes = read(fd, &rchar, 1);
    if(rchar == '\n')lines++;

    if(read_bytes < 0){
      perror("ERR: not reading!");
      return 2;
    }else if( read_bytes == 0){
      break;
    }
    buff[i++] = rchar;
  }

  wresult = write(STDOUT_FILENO, buff, i);
  if(wresult < 0){
    perror("ERR: write_ ");
    return 4;
  }

cresult = close(fd);
if(cresult < 0){
  perror("ERR close_");
  return 2;
}
  return 0;
}

int main(int argc, char *argv[]){

  for(int i = 1; i < argc; ++i)
  catFile(argv[i]);

  return 0;
}
