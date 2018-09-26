#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <dirent.h>
#include <string.h>

void listFiles(const char * path){
  DIR *dir;
  struct dirent *dp;

  //OPEN DIR STREAM
  if((dir = opendir(path)) == 0){
    perror("open");
    exit(1);
  }

  while ((dp = readdir(dir)) != NULL) {
    printf("%s\n", dp->d_name);
  }

  //CLOSE DIR STREAM
  closedir(dir);
}

int main(int argc, char const *argv[]) {

  listFiles(argv[1]);

  return 0;
}
