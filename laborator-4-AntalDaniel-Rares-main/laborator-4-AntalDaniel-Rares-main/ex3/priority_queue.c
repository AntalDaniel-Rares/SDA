#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct queue_node_t{
	int val;
    int priority;
	struct queue_node_t *next;
} queue_node_t;

typedef struct queue{
	struct queue_node_t *head;
	struct queue_node_t *tail;

	unsigned int length;
} queue_t;

queue_t *queue_create()
{
	queue_t *queue;

	queue = (queue_t *)malloc(sizeof(queue_t));
	queue->head = (queue_node_t *)malloc(sizeof(queue_node_t));
	queue->tail = (queue_node_t *)malloc(sizeof(queue_node_t));

	queue->head = NULL;
	queue->tail = NULL;
	queue->length = 0;

	return queue;
}

queue_node_t *queue_node_create(int val, int priority)
{
	queue_node_t *node;

	node = (queue_node_t *)malloc(sizeof(queue_node_t));
	node->val = val;
    node->priority = priority;
	node->next = NULL;

	return node;
}

void queue_push(queue_t *queue, int val, int priority)
{
	queue_node_t *node, *current;

	node = (queue_node_t *)malloc(sizeof(queue_node_t));
    current = (queue_node_t *)malloc(sizeof(queue_node_t));

	node = queue_node_create(val, priority);
    current = queue->head;

	if(queue->length != 0)
	{
        if(queue->tail->priority > priority)
            {
                queue->tail->next = node;
		        queue->tail = node;
            }
        else if(queue->head->priority < priority)
                {
                    node->next = queue->head;
                    queue->head = node;
                }
            else 
                {
                    while(current->next->priority >= priority)
                        {
							current = current->next;
						}
            
                    node->next = current->next;
                    current->next = node;   
                }
	}
	else 
	{
		//queue->tail = node;
		queue->head = queue->tail = node;
	}

	queue->length++;


}

void queue_print(queue_t *queue)
{
	queue_node_t *current;

	current = (queue_node_t *)malloc(sizeof(queue_node_t));

	current = queue->head;

    printf("\n");

	while(current != NULL)
	{
		printf("%d(priority: %d), ", current->val, current->priority);
		current = current->next;
	}

	printf("\n");

}

int queue_pop(queue_t *queue)
{
	int val = 0;

	queue_node_t *temp;

	temp = (queue_node_t *)malloc(sizeof(queue_node_t));

	if(queue->length != 0)
	{
		val = queue->head->val;
		temp = queue->head;

		queue->head = queue->head->next;

		free(temp);
		queue->length--;
	}
	else val = INT_MIN;  

	return val;
}

int main()
{
    queue_t *pq;
    int n, i = 0, val, priority;

    pq = queue_create();

    printf("n = ");
    scanf("%d", &n);

    while(i < n)
    {
        val = rand()%100;
		val = val*(rand()%2 ? -1 : 1);  

        priority = rand()%10 + 1;

        printf("%d(priority: %d), ", val, priority);

        queue_push(pq, val, priority);
        
        i++;
    }

    queue_print(pq);

    return 0;
}