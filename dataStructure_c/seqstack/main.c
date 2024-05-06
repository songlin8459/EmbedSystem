#include "seqstack.h"

int main()
{
    Seqstack *stack = Seqstack_Create();
    int i;
    for (i = 0; i < 10; i++)
    {
        Seqstack_Puch(stack, i);
    }
    int data = Seqstack_Pop(stack);
    printf("%d\n",data);
    return 0;
}