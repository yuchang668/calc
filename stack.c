#include "stack.h"

int stack_init(stack * p, int size)
{
	if (size <= 0) {
		return 0;
	}
	stack_type *tmp = (stack_type *) malloc(size * sizeof(stack_type));
	if (tmp == NULL) {
		return 0;
	}
	p->size = size;
	p->base = tmp;
	p->top = -1;
	return 1;
}

void stack_free(stack * p)
{
	free(p->base);
}

void stack_clear(stack * p)
{
    p->top = -1;
}

int stack_empty(stack * p)
{
	return p->top <= -1;
}

void stack_push(stack * p, stack_type item)
{
	if (p->top >= p->size - 1) {
		int newsize = p->top + 2;
		stack_type *tmp =
			(stack_type *) realloc(p->base, newsize * sizeof(stack_type));
		if (tmp == NULL) {
			return;
		}
		p->size = newsize;
		p->base = tmp;
	}
	p->base[++p->top] = item;
}

stack_type stack_pop(stack * p)
{
	if (!stack_empty(p)) {
		return p->base[p->top--];
	} else {
		return 0;
	}
}

stack_type stack_peek(stack * p)
{
	if (!stack_empty(p)) {
		return p->base[p->top];
	} else {
		return 0;
	}
}

char *stack_to_string(stack * p)
{
	int i;
	char *tmp = (char *)malloc((p->size + 1) * sizeof(char));
	if (tmp == NULL) {
		return NULL;
	}
	for (i = 0; i <= p->top; i++) {
		tmp[i] = (char)p->base[i];
	}
	tmp[i] = '\0';
	return tmp;
}
