#ifndef STACK_H

#define STACK_H

#include <stdlib.h>

typedef double stack_type;
typedef struct {
	int size;
	stack_type *base;
	int top;
} stack;

int stack_init(stack * p, int size);
void stack_free(stack * p);
void stack_clear(stack * p);
int stack_empty(stack * p);
void stack_push(stack * p, stack_type item);
stack_type stack_pop(stack * p);
stack_type stack_peek(stack * p);
char *stack_to_string(stack * p);

#endif /* end of include guard: STACK_H */
