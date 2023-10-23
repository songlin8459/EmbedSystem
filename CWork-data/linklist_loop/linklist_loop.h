#ifndef _LINKLIST_LOOP_H
#define _LINKLIST_LOOP_H
#define N 64
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int data_t;
typedef struct node
{
    data_t data;
    struct node *next;
}Node;




Node *Linklist_Loop_Create(void);//创建单向循环链表
void Linklist_Loop_Show(Node *head);//打印单向循环链表
void Linklist_Loop_Show_Head(Node *head);//打印无头单向循环链表
void Linklist_Loop_Insert_Head(Node *head, data_t data);//头部插入节点
int Linklist_Loop_Is_Empty(Node *head);//判空
void Linklist_Loop_Clear(Node *head);//清空
void Linklist_Loop_Destory(Node **head);//销毁
int Linklist_Loop_Get_Length(Node *head);//计算长
void Linklist_Loop_Insert_Pos(Node *head, int pos, data_t data);//按位置插入
void Linklist_Loop_Joseph(int num, int start, int count, int *output);//约瑟夫环
void Linklist_Delete_knowed(Node *knowed);//删除当前位置节点
Node *Linklist_Loop_Incor(Node *first, Node *second);//合并两条链表

#endif