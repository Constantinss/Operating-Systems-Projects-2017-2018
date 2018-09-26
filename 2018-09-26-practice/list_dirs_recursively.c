#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

void ListFilesRecursively(const char * basePath, const int root){
  DIR *dir;
  struct dirent *dp;
  char path[1000];

  struct stat buff;
  char mtime[1000];

  if((dir = opendir(basePath)) == 0){
    perror("opendir");
    exit(1);
  }

  while ((dp = readdir(dir)) != NULL) {
    if(dp->d_type == DT_DIR && strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){
      for (size_t i = 0; i < root; i++)
      printf(" | ");

      stat(dp->d_name, &buff);
      strcpy(mtime, ctime(&buff.st_mtime));
      printf("+%s %o %s\n", dp->d_name, buff.st_mode, mtime );

      strcpy(path,basePath);
      strcat(path, "/");
      strcat(path, dp->d_name);

      ListFilesRecursively(path, root + 2);
    }
  }
  closedir(dir);
}

int main(int argc, char const *argv[]) {

  ListFilesRecursively(argv[1], 0);
  return 0;
}
