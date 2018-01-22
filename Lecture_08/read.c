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
	while((rbytes = read(fd, buffer, SIZE)) != 0 ){
		write(STDIN_FILENO, buffer , rbytes);
	}
	close(fd);
	return 0;
}	
