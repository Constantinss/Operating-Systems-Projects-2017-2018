#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int bank_money[1000];
int bank_flag[1000];
pthread_mutex_t mutex[100];                      


void * transaction(void * arg){
  long n = (long) arg;
  for (size_t b = 0; b < 1000; b++) {
    pthread_mutex_lock(&mutex[n]);
      if(bank_money[n] != 0){
        bank_money[n] -= 50;
      }else{
        bank_flag[n] = 0;
      }
    pthread_mutex_unlock(&mutex[n]);
    pthread_mutex_lock(&mutex[n + 1]);
      if(bank_flag[n] != 0)
        bank_money[n + 1] += 50;
    pthread_mutex_unlock(&mutex[n + 1]);
  }

 pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {

  pthread_t banks_th[1000];
  int banks = 3;
  int trans = 2;

  if(argc > 2 && atoi(argv[1]) == atoi(argv[2]) + 1){
    banks = atoi(argv[1]);
    trans = atoi(argv[2]);
  }

  for (size_t c = 0; c < banks; c++) {
      pthread_mutex_init(&mutex[c], NULL);
  }

  for (size_t a = 0; a < banks; a++) {
      bank_money[a] = 1000;
      bank_flag[a] = 1;
  }

  for (size_t x = 0; x < trans; x++) {
    pthread_create(&banks_th[x], NULL, &transaction, (void*) x);
  }

  for (size_t y = 0; y < trans; y++) {
    pthread_join(banks_th[y],NULL);
  }

  for (size_t a = 0; a < banks; a++) {
      printf("bank:%ld  |  %d\n", a, bank_money[a]);;
  }

  return 0;
}
