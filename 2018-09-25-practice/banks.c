#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>
#include <ctype.h>

int banks_money[1000];
pthread_mutex_t mutex[1000];

//PTHREAD FOR TRANSACTIONS
void * transaction(void * arg){
  long n = (long) arg;

  for (size_t i = 0; i < 1000; i++) {
    pthread_mutex_lock(&mutex[n]);
    if(banks_money[n] != 0){
      banks_money[n] -= 50; //BANK1
    }
    pthread_mutex_unlock(&mutex[n]);

    pthread_mutex_lock(&mutex[n + 1]);
    if(banks_money[n] != 0){
      banks_money[n + 1] += 50; //BANK2
    }
    pthread_mutex_unlock(&mutex[n + 1]);
  }

  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {

  pthread_t banks_th[1000];
  int banks = 3; //bankers in all banks
  int trans = 2; //transaction

  //SET BANKERS & TRANSACTIONS
  if(argc > 2){
    if(atoi(argv[1]) == atoi(argv[2]) - 1){
      banks = atoi(argv[2]);
      trans = atoi(argv[1]);
    }else{
      perror("arguments");
      exit(-1);
    }
  }

  //SET MUTEXES FOR BANKS
  for (size_t i = 0; i < banks; i++) {
      pthread_mutex_init(&mutex[i], NULL);
  }

  //SET MONEY AT BANKS
  for (size_t i = 0; i < banks; i++) {
      banks_money[i] = 10000;
  }

  //CREATE PTHREADS
  for (size_t i = 0; i < trans; i++) {
      pthread_create(&banks_th[i], NULL, &transaction, (void *) i);
  }

  //JOIN PTHREADS
  for (size_t i = 0; i < trans; i++) {
      pthread_join(banks_th[i], NULL);
  }

  //DESTROY MUTEXES
  for (size_t i = 0; i < banks; i++) {
      pthread_mutex_destroy(&mutex[i]);
  }

  //SHOW MONEY AT BANKS
  for (size_t i = 0; i < banks; i++) {
      printf("bank:%ld | %d\n",i+1, banks_money[i]);
  }
  return 0;
}
