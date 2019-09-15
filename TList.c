#define _CRT_SECURE_NO_WARNINGS
#include "TList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "message.h"

void InitList(TList* Head){
	Head->head = NULL;
	Head->size = 0;
}
void AddInList(TList *Head, int name){
	TListElement **temp = &(Head->head);
	while (*temp){
		temp = &(*temp)->next;
	}
	*temp = (TListElement *)malloc(sizeof(TListElement));
	(*temp)->queue = createQueue();
	(*temp)->next = NULL;
	(*temp)->idx = name;
	Head->size++;
}

TListElement* FindElement(TList * Head, int ind){
	TListElement * element = Head->head;
	while (element && element->idx != ind){
		element = element->next;
	}
	return element;
}

bool PushMessage(TList* Head, Message_for_server mes){
	TListElement *element = FindElement(Head, mes.name);
	
	if (element){
		Queue *q = element->queue;
		pushQueue(q, mes.string);
		return true;
	}
	else{
		return false;
	}
}

char *PopMessage(TList *Head, Message_for_server mes){
	TListElement *element = FindElement(Head, mes.name);
	if (element&&element->queue->size != 0){
		strcpy(mes.string, popQueue(element->queue));
		return mes.string;
	}
	else{
		return "Massage queue is empty";
	}
}
