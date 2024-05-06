#include "linklist.h"
/*====================================创建头节点====================================*/
Node *Linklist_Create(void)
{
    Node *head = (Node *)malloc(sizeof(Node));
    if (NULL == head)
    {
        printf("malloc node failed!\n");
        return NULL;
    }
    head->next = NULL;
    return head;
}
/*====================================头部插入节点====================================*/
void Linklist_Insert_Head(Node *head, data_t data)
{
    Node *new = (Node *)malloc(sizeof(Node));
    if (NULL == head)
    {
        printf("malloc node failed!\n");
        return ;
    }
    new->data = data;
    new->next = NULL;

    new->next = head->next;
    head->next = new;
}
/*===========================按位置插入,插在pos后面，head为0位====================================*/
void Linklist_Insert_Pos(Node *head, int pos, data_t data)
{
    int len = Linklist_Get_Length(head);
    if(pos < 0 || pos > len)
    {
        printf("pos error!\n");
        return;
    }
    
    Node *new = (Node *)malloc(sizeof(Node));
    if (NULL == head)
    {
        printf("malloc node failed!\n");
        return ;
    }
    new->data = data;
    new->next = NULL;

    /*位置插入*/
    Node *p = head;
    for(int i; i < pos; i++)
    {
        p = p->next;
    }
    new->next = p->next;
    p->next = new;

}
/*====================================打印链表====================================*/
void Linklist_Show(Node *head)
{
    Node *p = head->next;
    while(p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
}
/*====================================计算表长====================================*/
int Linklist_Get_Length(Node *head)
{
    int len = 0;
    Node *p = head;
    while(p->next != NULL)
    {
        len++;
        p = p->next;
    }
    return len;
}

/*====================================删除pos+1节点，head为0====================================*/

void Linklist_Delete_Pos(Node *head, int pos)
{
    if(Linklist_Is_Empty(head) == 1)
    {
        printf("linklist is empty!\n");
        return;
    }
    int len = Linklist_Get_Length(head);
    if(pos < 0 || pos > len - 1)
    {
        printf("pos error!\n");
        return;
    }
    Node *p = head;
    /*得到pos的地址*/
    int i;
    for (i = 0; i < pos; i++)
    {
        p = p->next;
    }
    /*得到pos+1的地址*/
    Node *q = p->next;
    /*pos+2的地址付给pos的next*/
    p->next = q->next;
    /*释放pos+1位置的地址*/
    free(q);
    q = NULL;
}
/*====================================按值删除====================================*/
void Linklist_Delete_Data(Node *head, data_t data)
{
    if(Linklist_Is_Empty(head) == 1)
    {
        printf("linklist is empty!\n");
        return;
    }
    int i;
    /*p为头节点地址*/
    Node *p = head;
    /*q为第一个有效节点地址*/
    Node *q = head->next;
    for (i = 0; i < Linklist_Get_Length(head); i++)
    {
        if(q->data == data)
        {
            break;
        }
        p = p->next;
        q = q->next;   
    }
    p->next = q->next;
    /*free q*/
    free(q);
    q = NULL;
    return;
}
/*====================================判空====================================*/
int Linklist_Is_Empty(Node *head)
{
    if(head->next == NULL) return 1;
    else return 0;
}
/*====================================清空====================================*/
void Linklist_Clear(Node *head)
{
    Node *p = head, *q = NULL;
    while(p->next != NULL)
    {
        q = p->next;
        p->next = q->next;
        free(q);
        q = NULL;
    }
    return;
}
/*====================================销毁（调用清空函数）====================================*/
void Linklist_Destory(Node **head)
{
    Linklist_Clear(*head);
    free(*head);
    *head = NULL;
    return;
}
/*====================================销毁（不调用清空函数，递归方法）====================================*/
void Linklist_Destory2(Node **head)
{
    Node **p = head;
    while((*p)->next != NULL)
    {
        (*p) = (*p)->next;
        Linklist_Destory(p);
    }
    free(*p);
    *p = NULL;
    return;
}
/*====================================按位置查====================================*/
data_t Linklist_Search_Pos(Node *head, int pos)
{
    if(Linklist_Is_Empty(head) == 1)
    {
        printf("linklist is empty!\n");
        return -1;
    }
    if(pos < 0 || pos > Linklist_Get_Length(head) - 1)
    {
        printf("pos error!\n");
        return -1;
    }

    Node *p = head->next;
    for(int i = 0; i < pos; i++)
    {
        p = p->next;
    }
    return p->data;
}
/*====================================删除指定任意位置节点====================================*/
void Linklist_Delete_knowed(Node *knowed)
{
    /*判断是否为最后一个有效节点*/
    if(knowed->next == NULL)
    {
        knowed = NULL;
    }
    /*p为当前已知节点的地址，q为p下一节点的地址*/
    Node *p = knowed, *q = knowed->next;
    /*将下一节点的值赋给当前节点*/
    p->data = q->data;
    /*将下一节点的下一节点的地址赋给当前节点的指针域*/
    p->next = q->next;
    /*释放下一节点*/
    free(q);
    q = NULL;
}
/*====================================逆序====================================*/
void Linklist_Inverse(Node *head)
{
    /*把头节点的下一个节点地址给p*/
    Node *p = head->next;
    /*定义一个q，用来记录p*/
    Node *q = NULL;
    /*断开头节点*/
    head->next = NULL;
    
    while(p != NULL)
    {
        /*q记录下p的地址*/
        q = p;
        /*p指向下一个节点地址*/
        p = p->next;
        /*将q插入到头部节点后面*/
        q->next = head->next; 
        head->next = q;
    }
    return ;
}