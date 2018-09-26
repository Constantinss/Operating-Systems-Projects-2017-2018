#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
void ListFilesRecursively(const char * basePath, const int root){

  DIR *dir;
  struct dirent *ent;
  char path[1000];

  struct stat buff;
  char mtime[1000];

  if((dir = opendir(basePath)) == 0){
    perror("open");
    exit(-1);
  }

  while ((ent = readdir(dir)) != NULL) {

    if(ent->d_type == DT_DIR && strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0){

      for (size_t i = 0; i < root; i++)
      printf(" | ");

      stat(ent->d_name, &buff);
      strcpy(mtime, ctime(&buff.st_mtime));
      printf("+%s %ld %s\n", ent->d_name, buff.st_blksize , mtime);
      strcpy(path, basePath);
      strcat(path, "/");
      strcat(path, ent->d_name);

      ListFilesRecursively(path, root + 2);

    }
  }

  closedir(dir);
}


int main(int argc, char const *argv[]) {

  for (size_t i = 1; i < argc; i++){
    ListFilesRecursively(argv[i], 0);
  }

  return 0;
}
