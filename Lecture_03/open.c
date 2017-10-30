#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 100

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

	int fd = open(file, O_RDONLY);
	int cresult;
	ssize_t read_bytes, wresult;
	ssize_t written = 0;

	if( fd < 0){
		perror( "ERR: open_" );
		return 1;
	}
	while(1){
		written = 0;
		read_bytes = read(fd, buffer, SIZE);	
		if( read_bytes < 0){
			perror( "ERR: read_" );
			return 3;
		}else if( read_bytes == 0){
			break;
		}		

		while( written != read_bytes ){

		wresult = write(STDOUT_FILENO, buffer + written, read_bytes - written);
			if( wresult < 0){
				perror( "ERR: write_" );
				return 4;
			}
			written += wresult;
		}
	}
	cresult = close(fd);
	if( cresult < 0){
		perror( "ERR: close_" );
		return 2;
	}

 return 0;
}

/*
read more in ~$man 2 read

~$ gcc open.c -o open
~
~$ create file.txt
~
~$ ./open file.txt

how to write 1 to 100 numbers
~$ seq 1 100 > file.txt

*/
