//------------------------------------------------------------------------
// NAME: Constantin Mihaylov
// CLASS: XIb
// NUMBER: 13
// PROBLEM: #1
// FILE NAME: pthread.c (unix file name)
// FILE PURPOSE: create pthread.c
//------------------------------------------------------------------------

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define NUM_TFREADS 100
int count = 0;

void* is_prime(void *param){
	int flag = 1;
      //find the not prime
    	for (long i = 2; i <= (long)param/2; ++i)
    	{
    		if(  (long)param % i == 0){
    			flag = 0;
    			break;
    		}
    	}
    
    if(flag)count++; 
}


void* prime_list(void* param){
   void* status;
   int param0 = atoi(param);
   pthread_t tid[param0];
   
   for (int i = 2; i < param0; ++i)
   {
       pthread_create(&tid[i], NULL, is_prime, (void *)i);
       pthread_join(tid[i], NULL); 
   }  
   printf("Number of primes for N=%d is %d\n",param0, count);
   count = 0;
}


int main(int argc , char *argv[]){
    pthread_t tid;
    pthread_attr_t attr;
    size_t bufsize = 32;
    char *str;

    str = (char *)malloc(bufsize * sizeof(char));

    char* paramchar;
     getline(&str,&bufsize,stdin);
     paramchar = strtok(str, " ");
    while(*paramchar != 'e'){
            paramchar = strtok(NULL, " ");
                printf("Prime calculation started for N=%s",paramchar);
                //Get the default attributes
                pthread_attr_init(&attr);
                //Create the thread
                pthread_create(&tid,&attr,prime_list, paramchar);
                //Wait for the thread to exit
                pthread_join(tid, NULL);
                getline(&str,&bufsize,stdin);
                paramchar = strtok(str, " ");
    }    
    
    return 0;
}