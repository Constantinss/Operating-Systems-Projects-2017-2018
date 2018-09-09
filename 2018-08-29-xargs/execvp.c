#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	char * args[] = {"./helloExec", "Geeb" , "world", NULL};
	execvp("./helloExec", args);
	return 0;
}