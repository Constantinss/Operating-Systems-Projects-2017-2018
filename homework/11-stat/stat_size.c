       #include <sys/types.h>
       #include <sys/stat.h>
       #include <time.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <sys/sysmacros.h>
 
      int main(int argc, char *argv[])
       {
           struct stat sb;

           for (int i = 1; i < argc; ++i)
           {

	           if (stat(argv[i], &sb) == -1) {
	               perror("stat");
	               exit(EXIT_FAILURE);
	           }

	           printf("%s %lld\n",argv[i],(long long) sb.st_size);
	       }
           exit(EXIT_SUCCESS);
       }
