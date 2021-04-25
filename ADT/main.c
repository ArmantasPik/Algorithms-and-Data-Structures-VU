#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main()
{
    queue queue1, queue2;
    int counter;
    char *value;
    char *headValue;

    createQueue(&queue1);
    createQueue(&queue2);

    enqueue(&queue1, "hello");
    enqueue(&queue1, "there");
    enqueue(&queue2, "are");
    enqueue(&queue2, "possible");
    enqueue(&queue1, "cake");

    while(*(value = dequeue(&queue2)) != *queueEmpty)
        printf("dequeued value = %s\n", value);

    if(isEmpty(&queue1))
        printf("\nQueue is empty\n");
    else
        printf("\nQueue is not empty\n");

    headValue = getHeadValue(&queue1);
    printf("First element of the queue: %s\n", headValue);

    counter = getQueueCount(&queue1);
    printf("Number of elements in the queue: %d\n", counter);

    freeQueue(&queue1);

    headValue = getHeadValue(&queue1);
    printf("First element of the queue: %s\n", headValue);

    counter = getQueueCount(&queue1);
    printf("Number of elements in the queue: %d\n", counter);

    return 0;
}