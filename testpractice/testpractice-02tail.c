#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <fcntl.h>

int titleFunction(char* name, int currentSize){
  if(currentSize != 1)
  write(STDOUT_FILENO, "\n", 1);

  char * header = (char *)malloc(strlen(name) + 9);
  strcat(header, "==> ");
  strcat(header, name);
  strcat(header, " <==\n");
  int writingResult = write(STDOUT_FILENO, header, strlen(header));
  if(writingResult < 0){
    free(header);
    return 1;
  }
  free(header);

  return 0;
}

int stdWriteFunction(char * stdInput, int length, int currentSize){
  if(length > 2){
    titleFunction(stdInput, currentSize);
  }
  char * input = malloc(10);
  int element = 0, readingResult;
  char tmp[1];

  while(readingResult = read(STDIN_FILENO, tmp, 1) != 0){
    if(readingResult < 0){
      perror("tail: error reading");
      return 2;
    }
    if(element % 10 == 0){
      input = realloc(input, element + 10);
    }
    input[element++] = *tmp;
  }

  int lastTenLines = 0;
  int counter = 0;
  for(counter = element -1; counter > 0 && lastTenLines < 11; counter--){
    if(*(input + counter) == '\n')lastTenLines++;
  }

  if(lastTenLines == 11)counter +=2;

  int lines = 0;
  for(int i = counter; i < element; i++){
    int writingResult = write(STDOUT_FILENO, input + i, 1);
    if(writingResult < 0){
      perror("tail: error writing");
      return 1;
    }else{
      if(writingResult == 0){
        i--;
        continue;
      }
    }
    if(*(input + i) == '\n'){
      lines++;
    }
  }
  return 0;
}

void ErrorFunction(char * fileName){
  char *errorMessage = (char *) malloc(strlen("tail: error reading '") +
    strlen(fileName) +
    strlen("\'")
  );

  strcat(errorMessage, "tail: error reading '");
  strcat(errorMessage, fileName);
  strcat(errorMessage, "\'");
  perror(errorMessage);
  free(errorMessage);
}

int tailFunction(char * fileName, int length, int currentSize){
  int fd = open(fileName, O_RDONLY);
  if(fd < 0){

    char *errorMessage = (char *)malloc(strlen("tail: cannot open '") +
      strlen(fileName) +
      strlen("' for reading")
    );
    strcat(errorMessage, "tail: cannot open '");
    strcat(errorMessage, fileName);
    strcat(errorMessage, "' for reading");

    perror(errorMessage);
    free(errorMessage);
    return 1;
  }

  if(length > 2){
    titleFunction(fileName, currentSize);
  }

  char buf[1];

  int fileSize = lseek(fd, -1, SEEK_END);
  int lastTenLines = 0;
  int current = 1;

  while(lastTenLines < 11){
    int readingResult = read(fd, buf, 1);
    if(readingResult < 0){
        ErrorFunction(fileName);
        return 5;
    }
    if(*buf == '\n'){
      lastTenLines++;
    }
    if(lastTenLines < 11){
      current = lseek(fd, -2, SEEK_CUR);
    }
    if(current <= 0){
      break;
    }
  }
  int counter = current;
  while(counter < fileSize){
    int readResult = read(fd, buf, 1);
    if(readResult < 0){
        ErrorFunction(fileName);
        return 3;
    }else{
      if(readResult == 0){
        continue;
      }
    }

    int WritingResult = write(STDOUT_FILENO, buf, 1);
    if(WritingResult < 0){
      perror("tail: error writing");
      return 4;
    }else{
      if(WritingResult == 0){
        lseek(fd, -1, SEEK_CUR);
        continue;
      }
    }
    counter++;
  }

  if(lastTenLines < 11){
    int WritingResult = write(STDOUT_FILENO, "\n", 1);
    if(WritingResult < 0){
      perror("tail: error writing");
      return 6;
    }
  }
  if(close(fd) < 0){
    ErrorFunction(fileName);
    return 2;
  }
  return 0;
}

int main(int argc, char *argv[]){
  int standardInput = 1;
  int tailResult = -1;
  int checkFirst = 1;

  if(argc == 1){
    standardInput = stdWriteFunction("standard input", argc ,checkFirst);
  }
    for(int i = 1; i < argc; i++){
      if(checkFirst == 0){
        checkFirst = i;
      }
      if(argv[i][0] == '-' && argv[i][1] == '\0'){
        standardInput = stdWriteFunction("standard input", argc , checkFirst);
      }else{
        tailResult = tailFunction(argv[i], argc, checkFirst);
      }
      if(standardInput == 0 || tailResult == 0){
        checkFirst = 0;
      }
    }

  return 0;
}
