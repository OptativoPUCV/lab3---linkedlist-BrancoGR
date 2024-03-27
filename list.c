#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList()
{
  List * L = (List *)malloc(sizeof(List));
  L->head = NULL;
  L->tail = NULL;
  L->current = NULL;
  return L;
}

void * firstList(List *list)
{
  if(list->head == NULL)
    return NULL;
  list->current = list->head;
  return list->head->data;
}

void * nextList(List * list)
{
  if(list->current == NULL || list->current->next == NULL)
    return NULL;
  list->current = list->current->next;
  return list->current->data;
}

void * lastList(List * list)
{
  if(list->tail == NULL)
    return NULL;
  list->current = list->tail;
  return list->tail->data;
}

void * prevList(List * list)
{
  if(list->current == NULL || list->current->prev == NULL)
    return NULL;
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  if (newNode == NULL) return;
  newNode->data = data;
  newNode->prev = NULL;
  newNode->next = list->head;
  if(list->head != NULL)
    list->head->prev = newNode;
  list->head = newNode;
  if(list->tail == NULL)
    list->tail = newNode;
}

void pushBack(List * list, void * data)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  if (newNode == NULL) return;
  newNode->data = data;
  newNode->next = NULL;
  if(list->tail != NULL)
    list->tail->next = newNode;
  if(list->head == NULL)
    list->head = newNode;
  list->tail =newNode;
  list->current = list->tail;
  pushCurrent(list,data);  
}

void pushCurrent(List * list, void * data)
{
  Node *newNode = (Node*)malloc(sizeof(Node));
  if (newNode == NULL) return;
  newNode->data = data;
  newNode->next = list->current->next;
  newNode->prev = list->current;
  if(list->current->next != NULL)
    list->current->next->prev = newNode;
  list->current->next = newNode;
  if(list->current == list->tail)
    list->tail = newNode;
}

void * popFront(List * list)
{
  if(list->head == NULL)
    return NULL;
  list->head = list->head->next;
  if(list->head != NULL)
    list->head->prev = NULL;
  if(list->head == NULL)
    list->tail = NULL;
  list->current = list->head;
  return popCurrent(list);
}

void * popBack(List * list)
{
  if(list->tail == NULL)
    return NULL;
  list->tail = list->tail->prev;
  if(list->tail != NULL)
    list->tail->next = NULL;
  if(list->tail == NULL)
    list->head = NULL;
  list->current = list->tail;
  return popCurrent(list);
}

void * popCurrent(List * list)
{
  if (list->current == NULL)
    return NULL;
  Node *temp = list->current;
  void *data = temp->data;
  if (temp->prev != NULL)
    temp->prev->next = temp->next;
  else
    list->head = temp->next;
  if (temp->next != NULL)
    temp->next->prev = temp->prev;
  else
    list->tail = temp->prev;
  list->current = temp->next

}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}