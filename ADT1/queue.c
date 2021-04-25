#include "queue.h"

//Function that creates an empty queue
void createQueue(queue *currentQueue)
{
    currentQueue -> head = NULL;
    currentQueue -> tail = NULL;

    return;
}

//Function that checks if a queue is empty
bool isEmpty(queue *currentQueue)
{
    //Checking if queue is initialized
    if(currentQueue -> tail != NULL)
    {
        if(currentQueue -> tail -> next != NULL)
            return true;
    }

    if(currentQueue -> head == NULL)
        return true;
    else
        return false;
}

//Function that check if a queue is full
bool isFull(queue *currentQueue)
{
    //Checking if queue is initialized
    if(currentQueue -> tail != NULL)
    {
        if(currentQueue -> tail -> next != NULL)
            return false;
    }

    if(getQueueCount(currentQueue) == queueMax)
        return true;
    else 
        return false;
}

//Function that puts an element in the queue
bool enqueue(queue *currentQueue, varType value)
{
    //Checking if queue is initialized or full
    if(currentQueue -> tail != NULL)
    {
        if(currentQueue -> tail -> next != NULL)
        {
            printf("\nCannot enqueue, you have to create a queue first\n");
            return false;
        }
    }

    //Checking if queue is full
    if(getQueueCount(currentQueue) == queueMax)
    {
        printf("\nCannot add any more elements, queue is full!\n");
        return false;
    }
    
    //Creating a new node
    node *newNode = malloc(sizeof(node));

    if(newNode == NULL)
        return false;

    newNode -> value = value;
    newNode -> next = NULL;

    if(currentQueue -> head == NULL)
        currentQueue -> head = newNode;
    
    if(currentQueue -> tail != NULL)
        currentQueue -> tail -> next = newNode;

    currentQueue -> tail = newNode;

    return true;
}

//Function that returns the first element of the queue and removes it from the queue
varType dequeue(queue *currentQueue)
{
    //Checking if queue is initialized
    if(currentQueue -> tail != NULL)
    {
        if(currentQueue -> tail -> next != NULL)
        {
            printf("\nCannot dequeue, you have to create a queue first\n");
            return queueEmpty;
        }
    }

    //Checking if queue is full
    if(currentQueue -> head == NULL)
    {
        printf("Cannot dequeue more, because it is empty!\n");
        return queueEmpty;
    }

    //Defining a variable that takes the value that is inside of the dequeued block and making the headNode next Node in line
    node *tempNode = currentQueue -> head;
    varType dequeuedValue = currentQueue -> head -> value;
    currentQueue -> head = currentQueue -> head -> next;

    //If the last element is deleted then the tailNode is also the headNode, both equal to NULL
    if(currentQueue -> head == NULL)
        currentQueue -> tail = NULL;

    free(tempNode);

    return dequeuedValue;
}

//Function that gets the first element from the queue without deleting it from the queue
varType getHeadValue(queue *currentQueue)
{
    //Checking if queue is initialized
    if(currentQueue -> tail != NULL)
    {
        if(currentQueue -> tail -> next != NULL)
        {
            printf("\nYou have to create a queue first!\n");
            return queueEmpty;
        }
    }

    //Checking if queue is not empty
    if(currentQueue -> head == NULL)
    {
        printf("\nQueue is empty!\n");
        return queueEmpty;
    }

    return currentQueue -> head -> value;
}

//Function that returns an int that shows how many elements are in the queue
int getQueueCount(queue *currentQueue)
{
    //Checking if queue is initialized
    if(currentQueue -> tail != NULL)
    {
        if(currentQueue -> tail -> next != NULL)
        {
            printf("\nYou have to create a queue first!\n");
            return 0;
        }
    }

    if(currentQueue -> head == NULL)
        return 0;

    node *tempNode;
    tempNode = currentQueue -> head;
    int size = 0;

    while(tempNode != NULL)
    {
        size++;
        tempNode = tempNode -> next;
    }

    return size;
}

//Function that deletes the whole queue
void freeQueue(queue *currentQueue)
{
    //Checking if queue is initialized
    if(currentQueue -> tail != NULL)
    {
        if(currentQueue -> tail -> next != NULL)
        {
            printf("\nQueue is empty or not created!\n");
            return;
        }
    }

    //Checking if queue is not empty
    if(currentQueue -> head == NULL)
    {
        printf("\nQueue is already empty!\n");
        return;
    }

    //Deleting/Freeing every node until there are no elements left
    node *tempNode;
    while(currentQueue -> head != NULL)
    {
        tempNode = currentQueue -> head ->next;
        free(currentQueue -> head);
        currentQueue -> head = tempNode;
    }

    currentQueue -> tail = NULL;

    printf("\nQueue successfully freed!\n");

    return;
}