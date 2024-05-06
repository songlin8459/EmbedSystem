#include "linkstack.h"
/*===================================创建链式栈=======================================*/
Node *Linklist_Ceate(void)
{
    Node *head = (Node *)malloc(sizeof(Node));
    if(head == 0)
    {
        printf("malloc failed\n");
        return NULL;
    }
    head->next =  NULL;
    return head;

}
/*===================================入栈=======================================*/
void *Linklist_Push(Node *head, data_t data)
{
    /*创建节点*/
    Node *new = (Node *)malloc(sizeof(Node));
    if(new == 0)
    {
        printf("malloc failed\n");
        return NULL;
    }
    new->next =  NULL;
    new->data = data;
    /*入栈*/
    Node *p = head;
    new->next = p->next;
    p->next = new;
}
/*===================================出栈=======================================*/
data_t Linklist_Pop(Node *head)
{
    /*头节点的下一个节点地给p*/
    Node *p = head->next;
    /*p的值给pop*/
    data_t pop = p->data;
    /*p的下一个节点的地址给头节点的next*/
    head->next = p->next;

    /*释放p*/
    free(p);
    p = NULL;
    /*放回pop*/
    return pop;
}