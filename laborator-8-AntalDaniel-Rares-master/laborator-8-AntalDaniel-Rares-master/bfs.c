#include <stdio.h>
#include <stdlib.h>
#define SIZE 600

struct queue {
  int items[SIZE];
  int front;
  int rear;
};

typedef struct g{
    int V;
    int E;        
    int **a;
}Graph;

// Create a queue
struct queue* createQueue() {
  struct queue* q = malloc(sizeof(struct queue));
  q->front = -1;
  q->rear = -1;
  return q;
}

// Check if the queue is empty
int isEmpty(struct queue* q) {
  if (q->rear == -1)
    return 1;
  else
    return 0;
}

// Adding elements into queue
void enqueue(struct queue* q, int value) {
  if (q->rear == SIZE - 1)
    printf("\nQueue is Full!!");
  else {
    if (q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
  }
}

// Removing elements from queue
int dequeue(struct queue* q) {
  int item;
  if (isEmpty(q)) {
    printf("Queue is empty");
    item = -1;
  } else {
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
      //printf("Resetting queue ");
      q->front = q->rear = -1;
    }
  }
  return item;
}

// Print the queue
void printQueue(struct queue* q) {
  int i = q->front;

  if (isEmpty(q)) {
    printf("Queue is empty");
  } else {
    printf("\nQueue contains \n");
    for (i = q->front; i < q->rear + 1; i++) {
      printf("%d ", q->items[i]);
    }
  }
}

// BFS algorithm
void bfs(Graph* graph, int startVertex, int **list) 
{
  struct queue* q = createQueue();

  FILE *f;

  f = fopen("parcurgere_bfs.txt", "wt");

  int *visited;

  visited = (int*) calloc(graph->V, sizeof(int));

  visited[startVertex] = 1;
  enqueue(q, startVertex);

  while (!isEmpty(q)) 
  {
    int currentVertex = dequeue(q);
    fprintf(f, "Visited %s\n", list[currentVertex]);

    int* temp = graph->a[currentVertex];
    int i = 0;

    while (i < graph->V) 
    {
      if (visited[i] == 0 && temp[i] != 0) 
      {
        visited[i] = 1;
        enqueue(q, i);
      }
      i++;
    }
  }

  printf("\n");

}
