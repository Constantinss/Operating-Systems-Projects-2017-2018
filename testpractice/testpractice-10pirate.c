#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

pthread_mutex_t mut;
int water = 0;

void* sailorRemovesWater(void* arg_s){
    int index = 0;
    while(index < 20){
      while(pthread_mutex_trylock(&mut) != 0);

      if(water < 50){
        printf("The ship is dry, captain!\n");
      }else{
        water -= 50;
        printf("Sailor %ld removed 50 liters for the ship\n", ((long)arg_s + 1));
      }
      pthread_mutex_unlock(&mut);
      //sleep(2);
      index++;
    }

    pthread_exit(NULL);
}

void* pirateDoes(void* arg_p){
    int index = 0;
    while(index < 20){
      while(pthread_mutex_trylock(&mut) != 0);
      water += 50;
      //sleep(2);
      pthread_mutex_unlock(&mut);
      index++;
    }

    pthread_exit(NULL);
}

int main(int argc, char * argv[]){
  long sailor = 1;
  long pirate = 1;

  if(argc >= 2){
    pirate = atoi(argv[1]);
    sailor = atoi(argv[2]);
  }

  pthread_t thread_p[pirate];
  pthread_t thread_s[sailor];

  pthread_mutex_init(&mut, NULL);

  for(long i = 0; i < sailor; i++){
    pthread_create(&thread_p[i],NULL,&sailorRemovesWater, (void*) i);
  }

  for(long i = 0; i < pirate; i++){
    pthread_create(&thread_s[i],NULL,&pirateDoes,(void*) i);
  }


  for(long t = 0; t < pirate; t++){
    pthread_join(thread_p[t], NULL);
  }

  for(long t = 0; t < sailor; t++){
    pthread_join(thread_s[t], NULL);
  }


  printf("Water: %d\n", water);
  pthread_mutex_destroy(&mut);
  return 0;
}
