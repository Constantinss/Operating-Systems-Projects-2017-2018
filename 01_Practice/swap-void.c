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
