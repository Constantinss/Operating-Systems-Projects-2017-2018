//------------------------------------------------------------------------
// NAME: Konstantin Mihaylov
// CLASS: XIb
// NUMBER: 13
// PROBLEM: #3
// FILE NAME: swap.c
// FILE PURPOSE: 
// Swapping pointers.The function needs a way to refer to the original variables,
// not copies of their values. How can we refer to other variables in C? Using pointers.
//  The original values are not changed, because the function only swaps its own private copies.
//------------------------------------------------------------------------

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

