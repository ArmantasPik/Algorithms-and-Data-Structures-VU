#include "vector.h"
#include <stdio.h>

int main()
{
    vector cvector;

    VectorInit(&cvector);

    for(int i = 0; i<20; ++i)
    {
        VectorPushBack(&cvector, &i);
    }
    printf("\nPrinted elements: ");
    for(int i = 0; i < VectorSize(&cvector); ++i)
    {
        VAR *elem = (VAR*)VectorGet(&cvector, i);
        printf("%d ", *elem);
    }

    printf("\nVector size: %d", VectorSize(&cvector));

    for(int i = 0; i < 8; i++)
    {
        VectorDelete(&cvector, i);
    }

    printf("\nPrinted elements: ");
    for(int i = 0; i < VectorSize(&cvector); ++i)
    {
        VAR *elem = (VAR*)VectorGet(&cvector, i);
        printf("%d ", *elem);
    }

    for(int i = 0; i<10; ++i)
    {
        VectorSet(&cvector, i, &i);
    }

    printf("\nPrinted elements: ");
    for(int i = 0; i < VectorSize(&cvector); ++i)
    {
        VAR *elem = (VAR*)VectorGet(&cvector, i);
        printf("%d ", *elem);
    }

    VectorClear(&cvector);

    printf("\nPrinted elements: ");
    for(int i = 0; i < VectorSize(&cvector); ++i)
    {
        VAR *elem = (VAR*)VectorGet(&cvector, i);
        printf("%d ", *elem);
    }
    return 0;
}
