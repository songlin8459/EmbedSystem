#include<stdio.h>
#include<stdlib.h>

#ifndef _LINKLIST_H
#define _LINKLIST_H

typedef int data_t;
typedef struct node
{
    /* data */
    data_t data;
    /* pointer*/
    struct node *next;
}Node;

Node *Linklist_Create(void);//创建节点
void Linklist_Insert_Head(Node *head, data_t data);//头部插入
void Linklist_Insert_Pos(Node *head,int pos, data_t data);//位置插入
void Linklist_Show(Node *head);//打印表
int Linklist_Get_Length(Node *head);//计算表长
void Linklist_Delete_Pos(Node *head, int pos);//按位置删除
void Linklist_Delete_Data(Node *head, data_t data);//按值删除
int Linklist_Is_Empty(Node *head);//判空
void Linklist_Clear(Node *head);//清空
void Linklist_Destory(Node **head);//销毁（调用清空函数）
void Linklist_Destory2(Node **head);//销毁（不调用清空函数，递归方法）
data_t Linklist_Search_Pos(Node *head, int pos);//按位置查找
void Linklist_Delete_knowed(Node *knowed);//已知知一条单向链表中的某一个节点地址，要求删除当前节点
void Linklist_Inverse(Node *head);//逆序

#endif