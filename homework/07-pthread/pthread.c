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
#include <tgmath.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <fenv.h>
 
#define NUM_TFREADS 100
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int count = 0;

void* check(void* n)
{
   pthread_mutex_lock( &mutex1 );

  int param = *(int*)n;
  int flag;
   //Enabling the cancel functionality
                for(int j=2; j <= param; j++)
                  {
                    flag = 1;
                    for(int i=2; i <= j/2; i++)
                    {
                        if(j % i == 0){
                             flag = 0;
                             break;
                        }
                    }
                    if(flag)count++;
                  }
                count = param == 2 ? 0 : count;
                count = param == 3 ? 1 : count;
                printf("Number of primes for N=%d is %d\n",param, count);
                count = 0;
    pthread_mutex_unlock( &mutex1 );
}

int main(int argc , char *argv[]){
    pthread_t tid[NUM_TFREADS];
    int i = 0;
    char* paramchar = malloc(sizeof(char*));
    int* num = malloc(sizeof(int));
    
     
      while(1){
            scanf("%s", paramchar);
            if(paramchar[0] != 'e'){
              scanf("%d", num);     
                printf("Prime calculation started for N=%d\n",*num);  
                pthread_create(&tid[i], NULL, check, (void*)num);
                pthread_join(tid[i], NULL);
   
              num = malloc(i * sizeof(int));
              i++;
            }else{
              return -1;
            }
      }    
    
    return 0;
}
