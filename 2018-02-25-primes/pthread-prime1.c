//------------------------------------------------------------------------
// NAME: Constantin Mihaylov
// CLASS: XIb
// NUMBER: 13
// PROBLEM: #1
// FILE NAME: pthread.c (unix file name)
// FILE PURPOSE: create pthread.c
//------------------------------------------------------------------------
// https://www.cs.colorado.edu/~srirams/courses/csci2824-spr14/gmpTutorial.html

#include <pthread.h>
#include <stdio.h>
#include <tgmath.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <fenv.h>
 
#define NUM_TFREADS 100
int count = 0;

int check(long long int num)
{
    long long int i;
    if(num<=1)
        return 0;
    if(num==2)
        return 1;
    if(num%2==0)
        return 0;

   long double sRoot = sqrtl( (long double)num);
    for(i=3; i <= (int) sRoot; i+=2)
    {
        if(num%i==0)
            return 0;
    }
    return 1;
}


void* prime_list(void* arg){
  //catch the pthread_object as argument
   long param = atol(arg);
 
    //Enabling the cancel functionality
    for(long int i=2; i <= param; i++)
      {
          if(check(i))
          {
              count++;
          }
      }
    count = param == 2 ? 0 : count;
    count = param == 3 ? 1 : count;
    printf("Number of primes for N=%ld is %d\n",param, count);
    count = 0;
    pthread_exit((void *)param);
}


int main(int argc , char *argv[]){
    pthread_t tid[100];
    size_t bufsize = 32;
    char* paramchar;
    char* str;
    str = (char *)malloc(bufsize * sizeof(char));
    int i = 0;
     
     getline(&str,&bufsize,stdin);
     paramchar = strtok(str, " ");
     
    while(*paramchar != 'e'){
            paramchar = strtok(NULL, " ");
            printf("Prime calculation started for N=%s",paramchar);  
            //Create the thread
            pthread_create(&tid[i],NULL,prime_list, paramchar);
            //Wait for the thread to exit
            pthread_join(tid[i], NULL);
            i++;
            getline(&str,&bufsize,stdin);
            paramchar = strtok(str, " ");
    }    
    
    return 0;
}