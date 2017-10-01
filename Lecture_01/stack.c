//------------------------------------------------------------------------
// NAME: Konstantin Mihaylov
// CLASS: XIb
// NUMBER: 13
// PROBLEM: #6
// FILE NAME: stack.c
// FILE PURPOSE: 
// This program implements the stack functions. Stack is a LIFO data structure.
// Stack operations:
// void stack_init( stack * );
// void stack_destroy( stack * );
// int stack_full(stack * );
// int stack_empty( stack * );
// void stack_push( stack *, int );
// int stack_top( stack * );
// void stack_pop( stack * );
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	size_t size;
	size_t capacity;
	int *elements;
}stack;

void stack_init(stack*);
void stack_destroy(stack*);
void stack_push(stack*, int );
int stack_empty(stack*);
int stack_top(stack*);
void stack_pop(stack*);

int main(int argc, char* argv[])
{
	return 0;
}

int stack_empty(stack* stack)
{
	return stack->size == 0 ? 1 : 0;
}
void stack_pop(stack *stack)
{
	if((stack->size == 0))return;
	stack->size--;
}
int stack_top(stack *stack)
{
	if(0 == stack->size)return 0;
	return stack->elements[stack->size - 1];
}

void stack_push(stack *stack, int elem)
{
	if(stack->capacity == stack->size)
	{
		stack->capacity *= 2;
		stack->elements = realloc(stack->elements ,stack->capacity * sizeof(stack));
	}
	stack->elements[stack->size++] = elem;
}
void stack_destroy(stack *stack)
{
	stack->capacity = 0;
	stack->size = 0;
	free(stack->elements);
	stack->elements = NULL;
}
void stack_init(stack *stack){
	stack->capacity	= 50;
	stack->size = 0;
	stack->elements = malloc(stack->capacity * sizeof(stack));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

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
