struct queue;

typedef struct g Graph;

struct node* createNode(int);
struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
void display(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);
void bfs(Graph* g, int, char**);