/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* strcat( char* destination, const char* source );

int main()
{
    char stringOne[30];
    char stringTwo[30];
    fgets(stringOne,100,stdin);
    fgets(stringTwo,100,stdin);
     char* strResult = strcat(stringOne,stringTwo); 
     printf("%s", strResult);
    return 0;
}

char* strcat( char* destination, const char* source ){
   int j = 0;
    for(int i = strlen(destination)-1; i < strlen(destination) + strlen(source); i++){
	destination[i] = source[j];
	j++;
    }
    return destination;
}
*/
