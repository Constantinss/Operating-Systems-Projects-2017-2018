#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <pwd.h>
#include <sys/stat.h>



      int main(int argc, char *argv[])
       {
           struct stat sb;
           struct passwd *pwd;

           for (int i = 1; i < argc; ++i)
           {
              stat(argv[i], &sb);
              pwd = getpwuid(sb.st_uid);
              printf("%s %s\n",argv[i], pwd->pw_name);
  	       }
           exit(EXIT_SUCCESS);
       }
