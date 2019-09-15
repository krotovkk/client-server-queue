#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#define SIZE 80

Queue *createQueue(){
	Queue *q = (Queue*)malloc(sizeof(Queue));
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
	return q;
}

void pushQueue(Queue *q, char *mas){
	Node *n = (Node*)malloc(sizeof(Node));
	char *res = (char*)malloc(sizeof(char)*(strlen(mas)+1));
	strcpy(res,mas);
	n->item = res;
	
	if(q->head == NULL){
		q->head = n;
	}
	else{
		q->tail->next = n;
	}
	q->tail = n;
	q->size++;
}

char *popQueue(Queue* queue) {
    
    Node* head = queue->head;
    char *item = (char*)malloc(sizeof(char)*(strlen(head->item)+1));
    strcpy(item, head->item);
	
    queue->head = head->next;
    queue->size--;
   
    free(head);
    return item;
}

void deleteQueue(Queue *q){
	if (!q){
		return;
	}
	popQueue(q);
	deleteQueue(q);
	free(q);
}

void displayQueue(Queue *queue){
	printf("\nDisplay: ");
    	// no item
    	if (queue->size == 0)
        	printf("No item in queue.\n");
    	else { // has item(s)
        	Node *head = queue->head;
        	int i, size = queue->size;
        	printf("%d item(s):\n", queue->size);
        	for (i = 0; i < size; i++) {
           		if (i > 0) printf(", ");
            		printf("%s", head->item);
            		head = head->next;
        	}
    	}
    	printf("\n\n");
}
