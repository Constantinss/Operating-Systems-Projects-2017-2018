//------------------------------------------------------------------------
// NAME: Konstantin Mihaylov
// CLASS: XIb
// NUMBER: 13
// PROBLEM: #4
// FILE NAME: strdup.c
// FILE PURPOSE: 
// Swapping pointers if their values are above and below the size. That's somehow standard error case. 
// The function needs a way to refer to the original variables,
// not copies of their values. How can we refer to other variables in C? Using pointers.
// The original values are not changed, because the function only swaps its own private copies.
//------------------------------------------------------------------------

#include<stdio.h>

void swap(int* , int*, size_t);

int main(){
  int numberF, numberS, size;
  scanf("%d%d%d",&numberF, &numberS, &size);
 swap( &numberF, &numberS, size);
  printf("%d\n%d\n",numberF, numberS);
 
 return 0;
}

void swap(int *a,int *b, size_t size){
 int prm;
  if(size >= 0){
	 if(size > *a && size > *b){
		 prm = *b; *b = *a; *a = prm;		
		}else{
		 printf("Error!\n");		
		}
	}else{
	if(size < *a && size < *b){
		 prm = *b; *b = *a; *a = prm;		
		}else{
		 printf("Error!\n");		
		}
     } 
}
