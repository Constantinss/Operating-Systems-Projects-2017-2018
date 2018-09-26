#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
//PTHREAD
#include <pthread.h>
#include <ctype.h>

int banks_money[1000];
int flag_money[1000];
pthread_mutex_t mutex[1000];

void * transaction(void * arg) {
  long n = (long) arg;
  for (size_t c = 0; c < 1000; c++) {
    pthread_mutex_lock(&mutex[n]);
      if(banks_money[n] != 0){
        banks_money[n] -= 50;
      }else{
        flag_money[n] = 0;
      }
    pthread_mutex_unlock(&mutex[n]);
    pthread_mutex_lock(&mutex[n + 1]);
      if(flag_money[n] == 1)
      banks_money[n + 1] += 50;
    pthread_mutex_unlock(&mutex[n + 1]);
  }
  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {

  pthread_t banks_t[1000];
  int banks = 3; //basic case for banks
  int trans = 2;

  if(argc > 2 && atoi(argv[1]) == atoi(argv[2]) + 1){
    banks = atoi(argv[1]);
    trans = atoi(argv[2]);
  }

  //SET MUTEX
  for (size_t d = 0; d < banks; d++) {
    pthread_mutex_init(&mutex[d], NULL);
  }

  //SET MONEY
  for (size_t b = 0; b < banks; b++) {
    banks_money[b] = 10000;
    flag_money[b] = 1;
  }

  //CREATE PTHREAD
  for (long x = 0; x < trans; x++) {
    pthread_create(&banks_t[x], NULL, &transaction, (void*)x);
  }

  //JOIN PTHREAD
  for (size_t y = 0; y < trans; y++) {
    pthread_join(banks_t[y],NULL);
  }

  //SHOW THE MONEY IN THE BANKS
  for (size_t a = 0; a < banks; a++) {
    printf("bank:%ld\t|  %d\n",a+1, banks_money[a]);
  }

  return 0;
}
