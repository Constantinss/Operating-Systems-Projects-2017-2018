//------------------------------------------------------------------------
// NAME: Konstantin Mihaylov
// CLASS: XIb
// NUMBER: 13
// PROBLEM: #5
// FILE NAME: strdup.c
// FILE PURPOSE: 
// The strdup() function, available in various languages, 
// returns a pointer to a new string which is a duplicate of the original string.
// http://msdn.microsoft.com/en-us/library/windows/desktop/bb759969(v=vs.85).aspx
// https://developer.apple.com/library/mac/documentation/Darwin/Reference/ManPages/man3/strdup.3.html
// http://linux.die.net/man/3/strdup 
//------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *strdup( const char* );

int main(int argc, char* argv[])
{
  	char array[100];
 	scanf("%s", array);
	strdup(array);	
	return 0;
}
char * strdup( const char* old_arr )
{
	int strlength = strlen(old_arr);
	char *new_arr = malloc(strlength * sizeof(char));
	for(size_t i = 0; i < strlength; ++i)
	{
		*(new_arr + i) = *(old_arr + i);
	}
	return new_arr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include <stdlib.h>

#define SIZE_STR 10
char *strdup( const char * );

int main(){
  char str[10];
  fgets(str,10,stdin);
  printf("%s", strdup(str));
 return 0;
}

char *strdup(const char * s){
       
    char *string = malloc(sizeof(char *));
    char *destination = string; 
		
   
    
    while(*s != '\0'){
	
	 if(*s != '\t' && *s != '\n') {
            *string = *s;
	    s++ ; 
	    string++;
        	} else {
            ++s;
	}
   }
   *string = '\0';	
 return (char *)destination;
}
