#include "sequeue.h"
//创建循环队列
Sequeue *Sequeue_Create(void)
{
    Sequeue *queue = (Sequeue *)malloc(sizeof(Sequeue));
    if(queue == NULL)
    {
        printf("malloc failed!\n");
        return NULL;
    }
    queue->front = 0;
    queue->rear = 0;
}

//判空
int Sequeue_Is_Empty(Sequeue *queue)
{
    if((queue->rear + 1)%N == queue->front) return 1;
    else return 0;
}

//判满
int Sequeue_Is_Full(Sequeue *queue)
{
    if(queue->rear == queue->front) return 1;
    else return 0;
}
//计算队列元素个数
int Sequeue_Get_Length(Sequeue *queue)
{
    if(Sequeue_Is_Full(queue) == 1) return N-1;
    if(Sequeue_Is_Empty(queue) == 1) return 0;
    if(queue->front < queue->rear) return queue->rear -queue->front;
    if(queue->front > queue->rear) return N + queue ->rear -queue ->front;
}
//入队
void Sequeue_In(Sequeue *queue, data_t data)
{
    if((queue->rear + 1)%N == queue->front)
    {
        printf("queue is full!\n");
        return ;
    }

    queue->data[queue->rear] = data;
    queue->rear = (queue->rear + 1)%N;
    
}
//出队
data_t Sequeue_Out(Sequeue *queue)
{
    if(queue->rear == queue->front)
    {
        printf("queue is empty!\n");
        return -1;
    }

    data_t out = queue->data[queue->front];
    queue->front =  (queue->front + 1)%N;
    return out;
}
//销毁队列
void Sequeue_Destory(Sequeue **queue)
{
    free(*queue);
    *queue = NULL;
    return ;
}