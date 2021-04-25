#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*  1) Defining what variable type will be used in the queue (PVZ.: int, float, double) "varType" 
    2) Defining what to return if the queue is empty "queueEmpty",
    3) Defining how many elements can be placed in the queue "queueMax" */
#define varType char*
#define queueEmpty "-"
#define queueMax 256

typedef struct node
{
    varType value;
    struct node *next;
} node;

typedef struct queue
{
    node *head;
    node *tail;
} queue;

//Put your mouse cursor on function name and it will say what it does (if using VScode)

void createQueue(queue *currentQueue);
bool isEmpty(queue *currentQueue);
bool isFull(queue *currentQueue);
bool enqueue(queue *currentQueue, varType data);
varType dequeue(queue *currentQueue);
varType getHeadValue(queue *currentQueue);
int getQueueCount(queue *currentQueue);
void freeQueue(queue *currentQueue);

#endif