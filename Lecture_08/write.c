#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

#define SIZE 100
int main(){
	int fd = open("chat", O_WRONLY);
	char buffer[SIZE];
	ssize_t rbytes;
	while((rbytes = read(STDIN_FILENO, buffer, SIZE)) != 0 ){
		write(fd, buffer , rbytes);
	}
	close(fd);
	return 0;
}	
