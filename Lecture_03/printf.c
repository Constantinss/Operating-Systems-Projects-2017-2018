#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>

int main( ){

 const char *s = "Hello, world!";
 size_t len = strlen(s);
 ssize_t wresult;
 size_t written = 0;

	while(written != len){
	// wresult = write ( STDOUT_FILENO, s + written , len - written); // STDOUT_FILENO, STDIN_FILENO, STDERR_FILENO
	// wresult = syscall( SYS_write, STDOUT_FILENO, s + written , len - written); 
	__asm__ volatile ( "mov %[num], %%eax\n"
				 "mov %[fd], %%ebx\n"
				 "mov %[buff], %%ecx\n"
				 "mov %[to_write], %%edx\n"
				 "int $0x80\n"
				 "mov %%eax, %[wresult]\n"
				  : [wresult] "=r" (wresult)
				  : [num] "i" (SYS_write),
				    [fd] "i" (STDOUT_FILENO),
				    [buf] "m" (buf);
				    [to_write] "m" (to_write)
				:);

	  if(wresult  < 0){
	 	perror("There was a error!");
		return 1;
	  }
	  written += wresult;
	}
 return 0;
}

/*

~$ gcc printf.c -o filename //makes another buff 
~$ ./filename
~
~$ strace ./filename > /dev/null
~$ ./filename > /dev/full                                                                                                                                                                   
~$ man filename
~
__asm__

~$ gcc -m32 printf.c -o filename
~$ ./filename 

*/         
