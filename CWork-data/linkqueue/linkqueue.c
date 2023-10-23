#include "linkqueue.h"


//创建
Q *Linkqueue_Create(void)
{
    //给头部节点开辟空间
    Node *head = (Node *)malloc(sizeof(Node));
    if(head == NULL)
    {
        printf("Node malloc failed!\n");
        return NULL;
    }
    head->next = NULL;
    //给队头队尾指针开辟空间
    Q *lq = (Q *)malloc(sizeof(Q));
    if(lq ==NULL)
    {
        printf("Q malloc failed!\n");
        return NULL;
    }
    lq->front = head;
    lq->rear = head;
    return lq;
}
//入队
void Linkqueue_In(Q *lq, int data)
{
    //新节点开辟空间
    Node *new = (Node *)malloc(sizeof(Node));
    if(new == NULL)
    {
        printf("Node malloc failed!\n");
        return ;
    }
    new->next = NULL;
    new->data = data;
    //在尾部插入节点
    lq->rear->next = new;
    lq->rear = new;
    
}

//出队
int Linkqueue_Out(Q *lq)
{
    Node *p = lq->front->next;
    int data = p->data;
    lq->front->next = p->next;
    free(p);
    p = NULL;
    if(lq->front->next == NULL)
    {
        lq->rear = lq->front;
    }
    return data;
}