#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int catFiles(const char * fileName){
  char buff[1000];
  int counter = 0;
  int lines = 1;
  ssize_t read_bytes, write_bytes;
  int closeFile, openFile;
  char rchar;

  openFile = open(fileName, O_RDONLY);
  if(openFile < 0){
    perror("ERR: open_");
    return 2;
  }

  while(lines != 10){
    read_bytes = read(openFile,&rchar,1);
    if(read_bytes < 0){
      perror("ERR: read_");
      return 3;
    }else if(rchar == '\n'){
      lines++;
    }else if(read_bytes = 0){
      break;
    }

    buff[counter++] = rchar;
  }

  write_bytes = write(STDIN_FILENO, buff, counter);
  if(write_bytes < 0){
    perror("ERR: write_");
    return 4;
  }

  closeFile = close(openFile);
  if(closeFile < 0){
    perror("ERR: close_");
    return 5;
  }
  return 1;
}

int main(int argc, char* argv[]){

  for(int i = 1; i < argc; i++){
    catFiles(argv[i]);
  }
  return 0;
}
