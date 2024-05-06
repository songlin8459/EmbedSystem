#ifndef _SEQSTACK_H
#define _SEQSTACK_H

#include <stdio.h>
#include <stdlib.h>

#define N 64

typedef int data_t;
typedef struct seqstack
{
    data_t data[N];
    int top;
}Seqstack;

Seqstack *Seqstack_Create(void); //创建顺序栈
void Seqstack_Puch(Seqstack *stack, data_t data);//入栈
data_t Seqstack_Pop(Seqstack *stack);//出栈

#endif