#ifndef _LINKTREE_H
#define _LINKTREE_H
#include <stdio.h>
#include <stdlib.h>
#define N 64
typedef char data_t;

//二叉树
typedef struct  tree_node
{
    data_t data;
    struct  tree_node *l_child;
    struct  tree_node *r_child;

}Tree_node;

Tree_node *Linktree_Create(char *arr);//创建
void Linktree_Front(Tree_node *root);//先序遍历
void Linktree_Mid(Tree_node *root);//中序遍历
void Linktree_After(Tree_node *root);//后序遍历
void Linktree_Level(Tree_node *root);//层次遍历


//循环队列
typedef struct sequeue
{
    struct  tree_node *data[N];
    int front;
    int rear;
}Sequeue;

Sequeue *Sequeue_Create(void);//创建
void Sequeue_In(Sequeue *queue, Tree_node * data);//入队
Tree_node *Sequeue_Out(Sequeue *queue);//出队
void Sequeue_Destory(Sequeue **queue);//销毁




#endif