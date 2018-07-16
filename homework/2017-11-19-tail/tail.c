//------------------------------------------------------------------------
// NAME: Constantin Mihaylov
// CLASS: XIb
// NUMBER: 13
// PROBLEM: #2
// FILE NAME: tail.c
// FILE PURPOSE:
// the programm is efficiently implementing tail
//------------------------------------------------------------------------

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdarg.h>

int title(char *name, int currentSize) {
	if(currentSize != 1)
		write(STDOUT_FILENO, "\n", 1);

	char *header = (char *) malloc(strlen(name) + 9);
	strcat(header, "==> ");
	strcat(header, name);
	strcat(header, " <==\n");
	int write_result = write(STDOUT_FILENO, header, strlen(header));
	if(write_result < 0) {
		return 1;
	}
	free(header);

	return 0;
}

int stdWrite(char *stdInput, int length, int currentSize) {
	if(length > 2)title(stdInput, currentSize);
	char *input = malloc(10);
	int elem = 0, readResult;
	char tmp[1];

	while(readResult = read(STDIN_FILENO, tmp, 1) != 0) {
		if(readResult < 0) {
			perror("tail: error reading");
			return 2;
		}
		if(elem % 10 == 0)
			input = realloc(input, elem + 10);
		input[elem++] = *tmp;
	}

	int tenLines = 0;
	int counter = 0;
	for(counter = elem - 1; counter > 0 && tenLines < 11; counter--)
		if(*(input + counter) == '\n')tenLines++;

	if(tenLines == 11)
		counter += 2;

	int lines = 0;
	for(int i = counter; i < elem; i++) {
		int write_result = write(STDOUT_FILENO, input + i,  1);
		if(write_result < 0) {
			perror("tail: error writing");
			return 1;
		} else if(write_result == 0) {
			i--;
			continue;
		}
		if(*(input + i) == '\n') {
			lines++;
		}
	}

	return 0;
}

int tail(char *file_name, int length, int currentSize) {
	int fd = open(file_name, O_RDONLY);
	if(fd < 0) {
		/*specific message*/
		char *errorMessage = (char *) malloc(strlen("tail: cannot open '") +
			strlen(file_name) +
			strlen("' for reading"));
		strcat(errorMessage, "tail: cannot open '");
		strcat(errorMessage, file_name);
		strcat(errorMessage, "' for reading");
		/*The C library function void perror(const char *str) prints a descriptive error message to stderr.*/
		perror(errorMessage);
		free(errorMessage);
		return 1;
	}

	if(lengt > 2) {
		title(file_name, currentSize);
	}

	char buf[1];
	/*lseek is a system call that is used to change the location of
	 the read/write pointer of a file descriptor.
	 The location can be set either in absolute or relative terms.*/
	int file_size = lseek(fd,-1 , SEEK_END);
	int tenLines = 0;
	int cur = 1;
	while(tenLines < 11) {
		int readResult = read(fd, buf, 1);
		if(readResult < 0) {
			char *errorMessage = (char *) malloc(strlen("tail: error reading '") + strlen(file_name) + 1);
			strcat(errorMessage, "tail: error reading '");
			strcat(errorMessage, file_name);
			strcat(errorMessage, "\'");
			perror(errorMessage);
			free(errorMessage);
			return 5;
		}
		if(*buf == '\n') {
			tenLines++;
		}
		if(tenLines < 11) {
			cur = lseek(fd, -2, SEEK_CUR);
		}
		if(cur <= 0) {
			break;
		}
	}
	int counter = cur;
	while(counter < file_size) {
		int readResult = read(fd, buf, 1);
		if(readResult < 0) {
			char *errorMessage = (char *) malloc(strlen("tail: error reading '") + strlen(file_name) + 1);
			/*char *strcat(char *dest, const char *src)*/
			strcat(errorMessage, "tail: error reading '");
			strcat(errorMessage, file_name);
			strcat(errorMessage, "\'");
			perror(errorMessage);
			free(errorMessage);
			return 3;
		} else if(readResult == 0) {
			continue;
		}

		int write_result = write(STDOUT_FILENO, buf, 1);
		if(write_result < 0) {
			perror("tail: error writing");
			return 4;
		} else if(write_result == 0) {
			lseek(fd, -1, SEEK_CUR);
			continue;
		}
		counter++;
	}

	if(tenLines < 11) {
		int write_result = write(STDOUT_FILENO, "\n", 1);
		if(write_result < 0) {
			perror("tail: error writing");
			return 6;
		}
	}

	if(close(fd) < 0) {
		char *errorMessage = (char *) malloc(strlen("tail: error reading '") + strlen(file_name) + 1);
		strcat(errorMessage, "tail: error reading '");
		strcat(errorMessage, file_name);
		strcat(errorMessage, "\'");
		perror(errorMessage);
		free(errorMessage);
		return 2;

	}
	return 0;
}


int main(int argc, char **argv) {
	int standardInput = -1;
	int tailResult = -1;
	int checkFirst = 1;

	if(argc == 1)
		standardInput = stdWrite("standard input", argc, checkFirst);

	for(int i = 1; i < argc; i++) {
		if(checkFirst == 0) {
			checkFirst = i;
		}
		if(argv[i][0] == '-' && argv[i][1] == '\0') {
			standardInput = stdWrite("standard input", argc, checkFirst);
		} else {
			tailResult = tail(argv[i], argc, checkFirst);
		}
		if(standardInput == 0 || tailResult == 0) {
			checkFirst = 0;
		}
	}

	return 0;
}
