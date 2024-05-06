#include "seqstack.h"
/*===================================创建顺序栈=======================================*/
Seqstack *Seqstack_Create(void)
{
    /*开辟空间*/
    Seqstack *stack = (Seqstack *)malloc(sizeof(Seqstack));
    if(stack == NULL)
    {
        printf("malloc failed!\n");
        return NULL;
    }
    /*初始化top，表示创建的栈是空栈*/
    stack->top = -1;
    return stack;
}
/*===================================入栈=======================================*/

void Seqstack_Puch(Seqstack *stack, data_t data)
{
    if(stack->top == N - 1)
    {
        printf("stack is full!\n");
        return ;
    }
    stack->data[++(stack->top)] = data;
    return ;
}
/*===================================出栈=======================================*/
data_t Seqstack_Pop(Seqstack *stack)
{
    
    if(stack->top == -1)
    {
        printf("stack is empty!\n");
        return -1;
    }
    int pop = stack->data[stack->top--];
    
    return pop;
}