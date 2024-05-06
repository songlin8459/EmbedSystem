#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifndef _SEARCH_H
#define _SEARCH_H
typedef int data_t;
#define N 64
#define M 32

/*========================================顺序表===============================================*/
typedef struct seqlist
{
    data_t data[N]; /*存放顺序表的元素*/
    int last;/*表尾指针，用于表示最后一个元素下标*/
}Seqlist;

Seqlist *Seqlist_Create();//创建顺序表
void Seqlist_Insert_Pos(Seqlist *list, int pos, data_t data);//插入元素
void Seqlist_Show(Seqlist *list);//打印顺序表
int Seqlist_Is_Full(Seqlist *list);//判满
int Seqlist_Is_Empty(Seqlist *list);//判空
void Seqlist_Delete_Pos(Seqlist *list, int pos);//删除指定位置元素
void Seqlist_Delete_Data(Seqlist *list, data_t data);//删除指定数据元素
void Seqlist_Updata_Pos(Seqlist *list, int pos, data_t data);//修改指定位置元素
void Seqlist_Updata_Data(Seqlist *list, data_t data_original, data_t data_new);//修改指定数据元素
data_t Seqlist_Search_Pos(Seqlist *list, int pos);//查找指定位置元素
int Seqlist_Search_Data(Seqlist *list, data_t data);//查找指定数据元素
void Seqlist_Destory(Seqlist **plist);//删除表
int Search_Mid(Seqlist *list, data_t data);//折半查找

/*========================================单向链表===============================================*/
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
int Search_Hash(Seqlist *list, int len_old, int len_hash, int prime_number, data_t key);//哈希查找


#endif