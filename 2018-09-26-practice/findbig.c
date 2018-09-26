#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>





void listOfDirs(const char * basePath, const int root){

  DIR* dir;
  struct dirent *ent;
  char path[1000];
  struct stat buff;

  if((dir = opendir(basePath)) == 0){
    perror("opendir");
    exit(-1);
  }

  while((ent = readdir(dir)) != NULL){
    if(ent->d_type == DT_DIR && strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0){
      for (size_t i = 0; i < root; i++)
      printf(" | ");

      stat(ent->d_name, &buff);


      printf("+%s %ld\n", ent->d_name, buff.st_blksize);

      strcpy(path, basePath);
      strcat(path, "/");
      strcat(path, ent->d_name);

      listOfDirs(path, root + 2);

    }

  }
  closedir(dir);
}


int main(int argc, char const *argv[]) {

  for (size_t i = 1; i < argc; i++)
  listOfDirs(argv[i],0);

  return 0;
}
