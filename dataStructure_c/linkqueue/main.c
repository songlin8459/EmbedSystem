#include "linkqueue.h"

int main()
{
    Q *lq = Linkqueue_Create();
    int i;
    for(i = 0; i < 5; i++)
    {
        Linkqueue_In(lq, i);
    }

    for(i = 0; i < 2; i++)
    {
        printf("%d ", Linkqueue_Out(lq));
    }
    return 0;
}