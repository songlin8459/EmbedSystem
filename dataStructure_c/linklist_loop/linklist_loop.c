
#include "linklist_loop.h"

/*====================================创建头节点====================================*/
Node *Linklist_Loop_Create(void)
{
    Node *head = (Node *)malloc(sizeof(Node));
    if (NULL == head)
    {
        printf("malloc node failed!\n");
        return NULL;
    }
    head->next = head;
    return head;
}

/*====================================打印有头链表====================================*/
void Linklist_Loop_Show(Node *head)
{
    Node *p = head->next;
    while(p != head)
    {
        printf("%d ", p->data);
        p = p->next;
    }
}
/*====================================打印无头链表====================================*/
void Linklist_Loop_Show_Head(Node *head)
{
    Node *p = head;
    while(p->next != head)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("%d ", p->data);
}
/*====================================头部插入节点====================================*/
void Linklist_Loop_Insert_Head(Node *head, data_t data)
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
/*====================================判空====================================*/
int Linklist_Loop_Is_Empty(Node *head)
{
    if(head->next == head) return 1;
    else return 0;
}
/*====================================清空====================================*/
void Linklist_Loop_Clear(Node *head)
{
    Node *p = head, *q = NULL;
    while(p->next != head)
    {
        q = p->next;
        p->next = q->next;
        free(q);
        q = NULL;
    }
    return;
}
/*====================================销毁（调用清空函数）====================================*/
void Linklist_Loop_Destory(Node **head)
{
    Linklist_Loop_Clear(*head);
    free(*head);
    *head = NULL;
    return;
}
/*====================================计算表长====================================*/
int Linklist_Loop_Get_Length(Node *head)
{
    int len = 0;
    Node *p = head;
    while(p->next != head)
    {
        len++;
        p = p->next;
    }

    return len;
}

/*===========================按位置插入,插在pos个有效元素后面，head不是有效元素====================================*/
void Linklist_Loop_Insert_Pos(Node *head, int pos, data_t data)
{
    int len = Linklist_Loop_Get_Length(head);
    if(pos < 0)
    {
        printf("pos error!\n");
        return;
    }
    while(pos > len)
    {
        pos = len;
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
/*===========================按位置删除====================================*/
void Linklist_Loop_Delete_Pos(Node *head, int pos)
{
    
    int len = Linklist_Loop_Get_Length(head);

    while(pos > len)
    {
        pos = pos - len;
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
    return ;
}

/*====约瑟夫环:num节点数量，start计数开始位置，count步长，output输出数组=====*/
void Linklist_Loop_Joseph(int num, int start, int count, data_t *output)
{
    //创建头节点
    Node *joseph = Linklist_Loop_Create();
    joseph->data = 0;
    //创建其余num-1个其他节点
    int i = num - 1;
    while(i > 0)
    {
        Linklist_Loop_Insert_Head(joseph, i);
        i--;
    }
    //打印链表
    printf("linklsit : ");
    Linklist_Loop_Show_Head(joseph);
    printf("\n");   

    //确定开始计数节点地址
    Node *p = joseph;
    while(start--)
    {
        p = p->next;
    }
    //开始计数，删除，输出位置
    int k = 0, l;
    while(p->next != p)
    {
        //根据步长，确定删除的节点地址
        for(l = 0; l < count - 1; l++)
        {
            p = p->next;
        }
        //输出位置，此处节点值等于位置
        output[k] = p->data;
        k++;
        //删除当前节点
        Linklist_Delete_knowed(p);
    }
    //输出仅剩的一个节点位置
    output[k] = p->data;
    //释放仅剩的节点
    Linklist_Loop_Destory(&p);
    return ;
}

/*===============================删除当前位置节点=============================*/
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
/*===============================合并两条链表=============================*/
Node *Linklist_Loop_Incor(Node *first, Node *second)
{
    Node *p = first, *q = second;
    //找到first最后一个节点的地址
    while(p->next != first)
    {
        p = p->next;
    }
    //找到second最后一个节点的地址
    while(q->next != second)
    {
        q = q->next;
    }
    //第一条链表的表尾节点指向第二条链表的首个有效元素
    p->next = second->next;
    //第二条链表的表尾节点指向第一条链表的头节点
    q->next = first;
    return first;
}

