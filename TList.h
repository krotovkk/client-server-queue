#ifndef TLIST_H
#define TLIST_H

#include "queue.h"
#include <stdbool.h>
#include "message.h"


typedef struct TListElement{
	Queue *queue;
	int idx;
	struct TListElement *next;
}TListElement;
typedef struct TList{
	TListElement * head;
	int size;
}TList;
void InitList(TList* Head);
void AddInList(TList *Head, int name);
TListElement *FindElement(TList *Head, int ind);
bool PushMessage(TList *Head, Message_for_server mes);
char *PopMessage(TList *Head, Message_for_server mes);
#endif
