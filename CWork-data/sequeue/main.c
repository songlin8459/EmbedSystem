#include "sequeue.h"

int main()
{
    Sequeue *q = Sequeue_Create();
    int i;
    for(i =0; i < 5; i++)
    {
        Sequeue_In(q, i);
    }
    for(i = 0; i < 10; i++)
    {
        printf("%d ",Sequeue_Out(q));
    }
    printf("\n");
    
    //printf("%d\n",Sequeue_Out(q));
    Sequeue_Destory(&q);
    return 0;
}

