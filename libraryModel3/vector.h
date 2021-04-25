#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

#define VAR int

typedef struct {
    VAR *data;
    int size;
    int capacity;
} vector;

void VectorInit(vector * v);
int VectorSize(vector * v);
void VectorPushBack(vector * v, VAR * data);
int VectorSet(vector * v, int index, VAR * data);
void VectorDelete(vector * v, int index);
VAR * VectorGet(vector * v, int index);
void VectorClear(vector * v);

#endif // VECTOR_H
