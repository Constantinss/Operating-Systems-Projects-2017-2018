#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <poll.h>
#include <unistd.h>
#include <time.h>

#define SIZE 100
int main(){
	time_t rawtime;
  	struct tm * timeinfo;
	//wait for some event on a file descriptor
	struct pollfd mypoll = {STDIN_FILENO,POLLIN|POLLPRI}; 

	int fd;
	char wbuff[SIZE];
	char rbuff[SIZE];

	fd = open("chat",O_RDWR|O_NONBLOCK); //read and write mode
	
	while(1){
		time ( &rawtime );
  		timeinfo = localtime ( &rawtime );
		// memset() function fills the first n bytes of 
		// the memory area pointed to by s with the constant byte c. 
		memset(wbuff,'\0',SIZE);
		memset(rbuff,'\0',SIZE);
		//polling stdin for any input
		if(poll(&mypoll, 1, 2))
		{
			// open my fifo for write only
			fgets(wbuff, SIZE, stdin);
			write(fd, wbuff, sizeof(wbuff));
			//write(fd, wbuff, strlen(wbuff) + 1);
		}else{
			read(fd, rbuff, sizeof(rbuff));
			//read(fd, rbuff, strlen(rbuff) + 1);
		}
		 if((strlen(rbuff)) != 0){
		 		 //printing the received message and time
           		 printf("%s>> %s",asctime (timeinfo),rbuff);	
            }
	}
	return 0;
}	

// gcc chat.c
//first terminal ./a.out
//second terminal ./a.out