#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 100000
#define READ_LINES 10

int cat_file(const char *file);
int main( int argc, char **argv){

	int i;

	for(i = 1; i < argc; ++i){
		cat_file(argv[i] );
	}
return 0;
}

int cat_file (const char *file ){
	char buffer[SIZE];
	int i = 0;
	int fd = open(file, O_RDONLY);
	int cresult;
	int lines = 1;
	char rchar;
	ssize_t read_bytes, wresult;
	ssize_t written = 0;

	if( fd < 0){
		perror( "ERR: open_" );
		return 1;
	}
	
		while( lines != READ_LINES){
			read_bytes = read(fd, &rchar, 1);
			if(rchar == '\n')lines ++;
			
			if( read_bytes < 0 ){
				perror( "ERR: not reading!" );
				return 2;
			}else if( read_bytes == 0){
				break;
			}
			buffer[i++] = rchar;
		}	
  
       wresult = write(STDOUT_FILENO, buffer, i);
				if( wresult < 0){
					perror( "ERR: write_" );
					return 4;
				}	
	
	cresult = close(fd);
	if( cresult < 0){
		perror( "ERR: close_" );
		return 2;
	}

 return 0;
}
