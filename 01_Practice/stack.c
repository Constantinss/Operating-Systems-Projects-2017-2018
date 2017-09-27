//------------------------------------------------------------------------
// NAME: Konstantin Mihaylov
// CLASS: XIb
// NUMBER: 13
// PROBLEM: #6
// FILE NAME: stack.c
// FILE PURPOSE: 
// The purpose is to initialize the basic stack functions 
// void stack_init( stack * );
// void stack_destroy( stack * );
// int stack_full(stack * );
// int stack_empty( stack * );
// void stack_push( stack *, int );
// int stack_top( stack * );
// void stack_pop( stack * );
//------------------------------------------------------------------------

#include<stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 100
typedef struct
{
    size_t size;
    size_t capacity;
    int *elements;
} stack;

void stack_init( stack * );
void stack_destroy( stack * );
int stack_full(stack * );
int stack_empty( stack * );
void stack_push( stack *, int );
int stack_top( stack * );
void stack_pop( stack * );

int main(){
  
 return 0;
}

void stack_init( stack *st ){
 st->capacity = INITIAL_CAPACITY;
 st->size = 0;
 st->elements = malloc(INITIAL_CAPACITY * sizeof(int));
}

void stack_destroy( stack *st ){
 st->capacity = 0;
 st->size = 0;
 free(st->elements);
 st->elements = NULL;
}

int stack_empty( stack *st ){
 return st->size == 0;
}

int stack_full(stack* st) {
	return st->size == st->capacity;
}

void stack_push( stack *st, int val ){
 if(stack_full(st)){
	 st->elements = realloc(st->elements, st->capacity * 2);
  	 st->capacity *= 2;
	}
     st->elements[st->size++] = val;
}

int stack_top( stack * st ){
 if(stack_empty(st)){return 0;}
 return st->elements[st->size - 1];
}

void pop( stack * st){
 if(stack_empty(st)){return;}
 st->size--;
}
