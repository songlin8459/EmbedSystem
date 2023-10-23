#include "linklist_loop_double.h"
/*==============================创建双向循环链表===============================*/
Node *Linklist_Loop_Double_Create(void)
{
    Node *head = (Node *)malloc(sizeof(Node));
    if(head == NULL)
    {
        printf("malloc failed!\n");
        return 0;
    }
    head->prior = head;
    head->next = head;
}
/*==============================打印双向循环链表===============================*/
void Linklist_Loop_Double_Show(Node *head)
{
    Node *p = head->next;
    while(p != head)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return ;
}
/*==============================插入元素===============================*/
void Linklist_Loop_Double_Insert_Pos(Node *head, int pos, data_t data)
{
    /*创建新节点*/
    Node *new = (Node *)malloc(sizeof(Node));
    if(new == NULL)
    {
        printf("malloc failed!\n");
        return ;
    }
    new->prior = new;
    new->next = new;
    new->data = data;
    /*找到pos位置的地址*/
    Node *p = head;
    for(int i =0; i < pos; i++)
    {
        p = p->next;
    }

    /*插入链表*/
    new->next = p->next;
    p->next->prior = new;
    new->prior = p;
    p->next = new;
    return ;

}
/*==============================删除元素===============================*/
void Linklist_Loop_Double_Delete_Pos(Node *head, int pos)
{
    Node *p = head;
    /*找到要删除节点的地址，存放在指针p中*/
    for(int i =0; i <= pos; i++)
    {
        p = p->next;
    }
    /*改变指向*/
    p->next->prior = p->prior;
    p->prior->next = p->next;
    /*释放删除的节点*/
    free(p);
    p = NULL;
    return ;
}
/*==============================判空===============================*/
int Linklist_Loop_Double__Is_Empty(Node *head)
{
    if(head->next == head) return 1;
    else return 0;
}