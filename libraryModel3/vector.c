#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

void VectorInit(vector * v)
{
    v->capacity = 5;
    v->size = 0;
    v->data = (VAR*) malloc(5 * sizeof(VAR));
}

int IsVectorInit(vector * v)
{
    if(v->data != NULL)
    {
       return 1;
    }
    else
    {
       return 0;
    }
}

int IsThereMemory()
{
    VAR * memory = NULL;
    memory = (VAR*) malloc(sizeof(VAR));
    if(memory == NULL)
    {
        return 0;
    }
    else
    {
        free(memory);
        return 1;
    }
}

void VectorResize(vector * v)
{
    if(IsThereMemory() == 1)
    {
        v->capacity = v->capacity * 2;
        v->data = realloc(v->data, v->capacity * sizeof(VAR));
    }
    else
    {
        printf("\nError: there is no memory left.");
    }
}

int VectorSize(vector * v)
{
    return v->size;
}

void VectorPushBack(vector * v, VAR * data)
{
    if(IsVectorInit(v) == 1)
    {
        if(v->size >= v->capacity)
        {
            VectorResize(v);
            v->data[v->size] = *(VAR*) malloc(sizeof(VAR));
            memcpy(&(v->data[v->size]), data, sizeof(VAR));
            v->size++;
        }
        else
        {
            v->data[v->size] = *(VAR*) malloc(sizeof(VAR));
            memcpy(&(v->data[v->size]), data, sizeof(VAR));
            v->size++;
        }
    }
    else
    {
        printf("\nError: the vector was not initialized.");
    }
}

int VectorSet(vector * v, int index, VAR * data)
{
    if(IsVectorInit(v) == 1)
    {
        if(index >= 0 && v->size > index && v->size >= 1)
        {
            memcpy(&(v->data[index]), data, sizeof(VAR));
            return 1;
        }
        else if(index < 0)
        {
            printf("\nError: was typed a negative number.");
            return 0;
        }
        else
        {
            printf("\nError: was typed a number exceeding the size of the array.");
            return 0;
        }
    }
    else
    {
        printf("\nError: the vector was not initialized.");
        return 0;
    }
}

void VectorDelete(vector * v, int index)
{
    if(IsVectorInit(v) == 1)
    {
        if(index < 0)
        {
            printf("\nError: was typed a negative number.");
        }
        else if(index >= v->size)
        {
            printf("\nError: was typed a number exceeding the size of the array.");
        }
        else
        {
            for(int i = index; i < v->size - 1; ++i)
            {
                v->data[i] = v->data[i + 1];
            }
            v->size = v->size - 1;
        }
    }
    else
    {
        printf("\nError: the vector was not initialized.");
    }
}

VAR * VectorGet(vector * v, int index)
{
    if(IsVectorInit(v) == 1)
    {
        if(index < 0)
        {
            printf("\nError: was typed a negative number.");
            return NULL;
        }
        else if(index >= v->size)
        {
            printf("\nError: was typed a number exceeding the size of the array.");
            return NULL;
        }
        else
        {
            return &(v->data[index]);
        }
    }
    else
    {
        printf("\nError: the vector was not initialized.");
        return NULL;
    }
}

void VectorClear(vector * v)
{
    if(IsVectorInit(v) == 1)
    {
        v->size = 0;
        free(v->data);
    }
    else
    {
        printf("\nError: the vector was not initialized.");
    }
}
