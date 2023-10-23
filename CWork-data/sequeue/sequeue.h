#ifndef _SEQUEUE_H
#define _SEQUEUE_H
#include <stdio.h>
#include <stdlib.h>
#define N 64
typedef int data_t;

typedef struct sequeue
{
    data_t data[N];
    int front;
    int rear;
}Sequeue;

Sequeue *Sequeue_Create(void);//创建
void Sequeue_In(Sequeue *queue, data_t data);//入队
data_t Sequeue_Out(Sequeue *queue);//出队
void Sequeue_Destory(Sequeue **queue);//销毁
#endif