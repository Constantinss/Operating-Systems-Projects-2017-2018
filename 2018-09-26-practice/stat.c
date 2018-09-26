#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <time.h>
#include <string.h>

int main(int argc, char const *argv[]) {

  struct stat buf;
  char mtime[100];

  stat(argv[1], &buf);
  printf("st_mode = %o\n", buf.st_mode);

  strcpy(mtime, ctime(&buf.st_mtime));
  printf("st_mtime = %s", mtime );
  return 0;
}
