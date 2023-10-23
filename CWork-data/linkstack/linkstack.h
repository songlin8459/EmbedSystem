#ifndef _LINKSTACK_H
#define _LINKSTACK_H

#include <stdio.h>
#include <stdlib.h>

#define N 64

typedef int data_t;
typedef struct node
{
    data_t data;
    struct node *next;
}Node;

Node *Linklist_Ceate(void);//创建栈
void *Linklist_Push(Node *head, data_t data);//入栈
data_t Linklist_Pop(Node *head);//出栈
//销毁
#endif