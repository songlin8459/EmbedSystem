#ifndef _SEQUEUE_H
#define _SEQUEUE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node  *next;  
}Node;
typedef struct  linkqueue
{
    struct node *front;
    struct node *rear;
}Q;
Q *Linkqueue_Create(void);//创建
void Linkqueue_In(Q *lq, int data);//入栈
int Linkqueue_Out(Q *lq);//出栈

#endif