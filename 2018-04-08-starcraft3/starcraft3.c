//--------------------------------------------
//NAME: Konstantin Dimitrov Mihaylov
//CLASS:  Xib
//NUMBER:   13
//PROBLEM:   #3
//FILE NAME:  starcraft3.c
//FILE PURPOSE: 
// http://lubo.elsys-bg.org/wp-content/uploads/2016/11/HW03-threads.pdf
//---------------------------------------------

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

pthread_t * tids_scv;
int thread_scv_counter = 5;

int mineral_blocks = 2;
int mineral_block_counter = 2;
pthread_mutex_t * mineral_block_mutex;

int sum_of_minerals = 0;
int sum = 0;

int thread_marines_counter = 0;
int marines_count = 0;

pthread_mutex_t command_worker_mutex;
pthread_mutex_t marines_mutex;

int * minerals_p;

//thread for worker
//it is not sychronized and numbers of scves are mixed :D

void * scv(void * tmp) {
  //number of scv
  long n = (long) tmp + 1;

  int minerals_count = 0;
  int m = 0;
  //scv is mining in different miner blocks 
  while (sum != mineral_blocks * 500) {

    if (pthread_mutex_trylock( & mineral_block_mutex[m]) == 0) {

      if (minerals_p[m] > 0) {
        printf("SCV %ld is mining from mineral block %d\n", n, m + 1);
        sleep(3);

        if (minerals_p[m] < 8) {
          minerals_count = 4;
          minerals_p[m] -= 4;
        } else {
          minerals_p[m] -= 8;
          minerals_count = 8;
        }

        pthread_mutex_unlock( & mineral_block_mutex[m]);
        pthread_mutex_lock( & command_worker_mutex);
        printf("SCV %ld is transporting minerals\n", n);
        sleep(2);
        sum += minerals_count;
        sum_of_minerals += minerals_count;
        minerals_count = 0;
        printf("SCV %ld delivered minerals to the Command center\n", n);
        pthread_mutex_unlock( & command_worker_mutex);

      }

    }
    if (m == (mineral_blocks - 1)) {
      m = 0;
    } else {
      m++;
    }

  }
  return NULL;
}

int main(int argc, char * * argv) {
  pthread_mutex_init( & command_worker_mutex, NULL);
  pthread_mutex_init( & marines_mutex, NULL);

  long create_scv = 0;
  //takes mineral blocks
  if (atoi(argv[argc - 1]) > 0)
    mineral_block_counter = atoi(argv[argc - 1]);
  mineral_blocks = mineral_block_counter;
  //dynamic creating of array of mineral_block_mutex-es
  if ((mineral_block_mutex = malloc(sizeof(pthread_mutex_t) * mineral_block_counter)) == NULL) {
    perror("Error: malloc of mineral_block_mutex!\n");
    exit(-1);
  }
  //dynamic creating of minerals for blocks
  if ((minerals_p = malloc(sizeof(int) * mineral_block_counter)) == NULL) {
    perror("Error: malloc of minerals_p!\n");
    exit(-1);
  }
  //init minerals_p
  for (int i = 0; i < mineral_block_counter; ++i) {
    minerals_p[i] = 500;
  }

  //creates threads for scv
  if ((tids_scv = malloc(sizeof(pthread_t) * thread_scv_counter)) == NULL) {
    perror("Error: malloc of tids_scv!\n");
    exit(-1);
  }
  //init mutex array mineral_blocks
  for (int i = 0; i < mineral_block_counter; ++i) {
    pthread_mutex_init( & mineral_block_mutex[i], NULL);
  }

  //creating fitst five scv
  for (create_scv = 0; create_scv < thread_scv_counter; create_scv++) {
    if (pthread_create( & tids_scv[create_scv], NULL, scv, (void * ) create_scv) != 0) {
      perror("Error: create pthread!\n");
      exit(-1);
    }
  }
  //checking if marines_count
  while (marines_count < 20) {
    char in = getchar();
    switch ( in ) {

    case 'm':
      pthread_mutex_lock( & command_worker_mutex);
      if (sum_of_minerals >= 50) {

        pthread_mutex_lock( & marines_mutex);
        sum_of_minerals -= 50;
        sleep(1);
        marines_count++;
        printf("You wanna piece of me, boy?\n");
        pthread_mutex_unlock( & marines_mutex);
      } else {

        printf("Not enough minerals\n");

      }
      pthread_mutex_unlock( & command_worker_mutex);
      break;

    case 's':
      pthread_mutex_lock( & command_worker_mutex);
      if (sum_of_minerals >= 50) {
        sum_of_minerals -= 50;
        thread_scv_counter++;

        if (thread_scv_counter != 0) {
          if ((tids_scv = realloc(tids_scv, sizeof(pthread_t) * thread_scv_counter)) == NULL) {

            perror("Error: realloc!\n");
            exit(-1);

          } else {

            if (pthread_create( & tids_scv[create_scv++], NULL, scv, (void * ) create_scv) != 0) {
              perror("Error: create pthread!\n");
              exit(-1);
            } else {
              if (thread_scv_counter > 5)
                printf("SCV good to go,sir.\n");
            }
          }

        }

      } else {

        printf("Not enough minerals\n");

      }
      pthread_mutex_unlock( & command_worker_mutex);
      break;
    }
  }
  for (long join_scv = 0; join_scv < thread_scv_counter; ++join_scv) {

    if (pthread_join(tids_scv[join_scv], NULL) != 0) {
      perror("Error: join pthread!\n");
      exit(-1);
    }
  }
  printf("Map minerals %d, player minerals %d, SCVs %d, Marines %d\n", mineral_blocks * 500, sum_of_minerals, thread_scv_counter, marines_count);

  pthread_mutex_destroy(mineral_block_mutex);
  free(mineral_block_mutex);

  pthread_mutex_destroy( & command_worker_mutex);
  pthread_mutex_destroy( & marines_mutex);
  free(minerals_p);
  free(tids_scv);

  pthread_exit(NULL);

}