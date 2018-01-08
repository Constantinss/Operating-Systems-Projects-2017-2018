#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define SIZE 10000

int main(int argc, char **argv){
  int file_open = open(argv[1], O_RDONLY);
  int spacenum_bytes = atoi(argv[2]);
  int write_bytes = atoi(argv[3]);
  int cresult; 
        if(file_open < 0){
             	perror("ERR: open!");
                return 1;
            }
 
        char buffer[SIZE];
        int lsick = lseek(file_open,spacenum_bytes,SEEK_SET);
        int read_bytes, wresult;
        int count = 0;
        char rchar;

        	while( count < write_bytes ){
				read_bytes = read(file_open, &rchar, 1);
						
				if( read_bytes < 0 ){
					perror( "ERR: not reading!" );
					return 2;
				}else if( read_bytes == 0){
					break;
				}
				buffer[count++] = rchar;
				if(rchar == '\n'){
				   break;
				}
			}

			if( read_bytes <= 0 ){
				perror( "ERR: not reading!" );
				return 2;
			}
		wresult = write(STDOUT_FILENO, buffer, count);
	
			if( wresult < 0){
				perror( "ERR: write!" );
				return 4;
			}	
	
		cresult = close(file_open);
			
			if( cresult < 0){
				perror( "ERR: close!" );
				return 3;
			}

 return 0;
}
