#include<stdio.h>

void swap(int* , int* );

int main(){
  int numberF, numberS;
  scanf("%d%d",&numberF, &numberS);

 swap( &numberF, &numberS);
 printf("%d\n%d\n",numberF, numberS);

 return 0;
}

void swap(int *a,int *b){
 int prm;
 prm = *b;
 *b = *a;
 *a = prm;
}
