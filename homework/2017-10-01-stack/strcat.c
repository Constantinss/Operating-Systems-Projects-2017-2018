//------------------------------------------------------------------------
// NAME: Konstantin Mihaylov
// CLASS: XIb
// NUMBER: 13
// PROBLEM: #2
// FILE NAME: strcat.c
// FILE PURPOSE: 
// It takes two arguments, i.e, two strings or character arrays,
// and stores the resultant concatenated string in the first string specified in the argument.
//The pointer to the resultant string is passed as a return value. 
//------------------------------------------------------------------------

#include <stdio.h>
#define ARG_SIZE 100

char* strcat( char* destination, const char* source);
int main(int argc, char *argv[])
{
	char destination_arr[ARG_SIZE];
	char source_arr[ARG_SIZE];
	scanf("%s%s", destination_arr, source_arr);
	printf("%s", strcat(destination_arr, source_arr));	

	return 0;
}

char* strcat( char* destination, const char* source)
{
	size_t i;
	for( i = 0; destination[i] != '\0'; ++i);
	for(size_t k = 0; source[k] != '\0'; ++k)
		destination[i + k] = source[k];

	return destination;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define SIZE_STR 30
char* strcat( char* destination, const char* source );
int main()
{
    char stringOne[SIZE_STR];
    char stringTwo[SIZE_STR];
    fgets(stringOne,SIZE_STR,stdin);
    fgets(stringTwo,SIZE_STR,stdin);      
     printf("%s", strcat(stringOne,stringTwo));
    return 0;
}

char* strcat( char* destination, const char* source ){

    const unsigned char *d = (const unsigned char *)destination;
    const unsigned char *s = (const unsigned char *)source;
 
    char *string;
    destination = string; 
		
   
    
    while(*d != '\0'){
	
	 if(*d != '\t' && *d != '\n') {
            *string = *d;
	    d++ ; 
	    string++;
        } else {
            ++d;
        }

	if(*d == '\0'){
		while(*s != '\0'){
			
			 if(*s != '\t' && *s != '\n') {
            			*string = *s;
	    			s++ ; 
	   			string++;
        		} else {
           			++s;
        		}
		 }
	      }
           }
      *string = '\0';
	
    return (char *)destination;
  //much more better
  /*
	char *string = malloc(strlen(d) + strlen(s) + 1);
	char *res = string;
	for (; *d ; *string++ = *d++);
	for (; *s ; *string++ = *s++);
	*string = '\0';
	return res;
  */
}
