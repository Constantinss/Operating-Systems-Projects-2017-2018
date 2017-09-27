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
