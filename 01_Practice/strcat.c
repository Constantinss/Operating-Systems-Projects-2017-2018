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
 
    char *string = malloc(sizeof(char *));
    char *res = string;
		
   
    
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
    return (char *)res;
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
