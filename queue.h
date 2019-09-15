#ifndef H_QUEUE
#define H_QUEUE

typedef struct Node{
	char *item;
	struct Node *next;
}Node;

typedef struct Queue{
	Node *head;
	Node *tail;

	int size;
}Queue;

Queue *createQueue();
void pushQueue(Queue *q, char *mas);
char *popQueue(Queue* queue);
void deleteQueue(Queue *q);
#endif
