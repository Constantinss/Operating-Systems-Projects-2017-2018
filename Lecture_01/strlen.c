//------------------------------------------------------------------------
// NAME: Konstantin Mihaylov
// CLASS: XIb
// NUMBER: 13
// PROBLEM: #1
// FILE NAME: strlen.c
// FILE PURPOSE: 
// The function takes a single argument,
// the string variable whose length is to be found,
// and returns the length of the string passed.
//------------------------------------------------------------------------

#https://elsys.github.io/os-homeworks/tasks/2017/09/25/strcat
#https://stackoverflow.com/questions/2524611/how-can-one-print-a-size-t-variable-portably-using-the-printf-family

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t strlen(const char * );

int main()
{
    char string[100];
    fgets(string,100,stdin);
     size_t result = strlen(string);
     printf("%zx", result);
    return 0;
}

size_t strlen(const char * str ){
    int count = 0;
    for (;str[count] != '\0'; count++) {}
    return count;
}

