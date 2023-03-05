#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

typedef struct stack_node_t{
	char s[15];
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

stack_node_t *stack_node_create(char *string)
{
	stack_node_t *node;

	node = (stack_node_t *)malloc(sizeof(stack_node_t));
	strcpy(node->s,string);
	node->next = NULL;

	return node;
}

void stack_push(stack_t *stack, char *string)
{
	stack_node_t *node;

	node = (stack_node_t *)malloc(sizeof(stack_node_t));

	node = stack_node_create(string);
	node->next = stack->head;
	stack->head = node;

	stack->length++;

}

void stack_print(stack_t *stack)
{

	stack_node_t *node;

	node = (stack_node_t *)malloc(sizeof(stack_node_t));

	node = stack->head;

	while(node != NULL)
	{
		printf("%s ",node->s);

		node = node->next;
	}

}

char *stack_pop(stack_t *stack)
{
	char *string;

    string = (char *)malloc(15*sizeof(char));

	stack_node_t *temp;

	temp = (stack_node_t *)malloc(sizeof(stack_node_t));

	if(stack->head != NULL)
	{
		strcpy(string, stack->head->s);
		temp = stack->head;
		stack->head = stack->head->next;

		free(temp);

		stack->length--;
	}
	else string = NULL;

	return string;

}

int main()
{
    FILE* f;

    f = fopen("input.txt", "rt"); 

    stack_t *stack;

    stack = stack_create();
    
    char *str;

    str = (char *)malloc(15*sizeof(char));

    while (fscanf(f,"%s",str) != EOF)
    {
        stack_push(stack,str);
    }

	fclose(f);

	f = fopen("output.txt", "wt");

    while(stack->length)
    {
        str = stack_pop(stack);
        fprintf(f, "%s " , str);

    }
    
	fclose(f);

    return 0;
}