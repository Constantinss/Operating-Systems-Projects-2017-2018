#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <dirent.h>
#include <string.h>
/* Defines DT_* constants */
#include <fcntl.h>
#include <sys/syscall.h>

void listDir(char* path){
DIR* dir;
struct dirent *ent;
  if((dir=opendir(path)) != NULL){
    printf("\n-------DIR--------\n");
    while (( ent = readdir(dir)) != NULL){
      if(ent->d_type == DT_DIR && strcmp(ent->d_name, ".") != 0  && strcmp(ent->d_name, "..") != 0){
        printf("%s\n", ent->d_name);
        //path + "/" + d_name
        //strcat(path, "/" );
        //strcat(path, ent->d_name);
        listDir(ent->d_name);
      }
    }
    closedir(dir);
  }
}
int main(int argc, char* argv[]){
  listDir("../../");

  return 1;
}

/*
  st-> st_size;
*/
