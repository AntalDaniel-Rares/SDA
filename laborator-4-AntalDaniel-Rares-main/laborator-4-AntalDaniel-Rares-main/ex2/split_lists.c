#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

typedef struct stack_node_t{
	int val;
	struct stack_node_t *next;
} stack_node_t;

typedef struct stack{
	struct stack_node_t *head;
	unsigned int length;
} stack_t;


stack_t *stack_create()
{
	stack_t *stack;

	stack = (stack_t *)malloc(sizeof(stack_t));
	stack->length = 0;

	stack->head = (stack_node_t *)malloc(sizeof(stack_node_t));
	stack->head = NULL;

	return stack;
}

stack_node_t *stack_node_create(int val)
{
	stack_node_t *node;

	node = (stack_node_t *)malloc(sizeof(stack_node_t));
	node->val = val;
	node->next = NULL;

	return node;
}

void stack_push(stack_t *stack, int val)
{
	stack_node_t *node;

	node = (stack_node_t *)malloc(sizeof(stack_node_t));

	node = stack_node_create(val);
	node->next = stack->head;
	stack->head = node;

	stack->length++;

}

void stack_print(stack_t *stack)
{

	stack_node_t *node;

	node = (stack_node_t *)malloc(sizeof(stack_node_t));

	node = stack->head;
    
    printf("\n");

	while(node != NULL)
	{
		printf("%d, ",node->val);

		node = node->next;
	}

	printf("\n");

}

char stack_pop(stack_t *stack)
{
	int val = 0;

	stack_node_t *temp;

	temp = (stack_node_t *)malloc(sizeof(stack_node_t));

	if(stack->head != NULL)
	{
		val = stack->head->val;
		temp = stack->head;
		stack->head = stack->head->next;

		free(temp);

		stack->length--;
	}
	else val = INT_MIN;

	return val;

}

int stack_empty(stack_t *stack)
{
	if(stack->head == NULL)
		return 1;

	return 0;
}

int stack_top(stack_t *stack)
{
	int val = 0;

	if(stack->head != NULL)
	{
		val = stack->head->val;
	}
	else val = INT_MIN;

	return val;
}

void stack_split(stack_t *stack, stack_t *plus, stack_t *minus)
{
    int val = 0;

    while(!stack_empty(stack))
    {
        val = stack_top(stack);

        if(val >= 0)
            stack_push(plus, val);
        else stack_push(minus, val);
                
        stack_pop(stack);  
    }

}

int main()
{
    int *a, n, i=0;

    printf("n = ");
    scanf("%d", &n);

    a = (int *)malloc(n*sizeof(int));

    while(i<n)
    {
        if(rand()%2)
            *(a+i) = rand()%100;
        else *(a+i) = (-1)*rand()%100;
        i++;
    }

    stack_t *stack, *plus, *minus;

    stack = stack_create();
    plus = stack_create();
    minus = stack_create();
  
    i = 0;
    while(i<n)
    {
        stack_push(stack, *(a+i));
        printf("%d ", *(a+i));
        i++;
    }

    free(a);

    stack_split(stack, plus, minus);

    free(stack);

    stack_print(plus);
    stack_print(minus);

    free(plus);
    free(minus);

    return 0;
}