#include "linktree.h"
//创建链式二叉树并存储
Tree_node *Linktree_Create(char *arr)
{
    char data;
    //scanf("%c", &data);
    static int i = 0;
    data = arr[i++];
    Tree_node *root = NULL;
    if(data != '#')
    {
        root = (Tree_node *)malloc(sizeof(Tree_node));
        root->data = data;
        root->l_child = Linktree_Create(arr);
        root->r_child = Linktree_Create(arr);
    }
    else return NULL;
    return root;
}
//先序遍历：根-左-右
void Linktree_Front(Tree_node *root)
{
    if(root == NULL)
    {
        return ;
    }
    printf("%c", root->data);
    Linktree_Front(root->l_child);
    Linktree_Front(root->r_child);
}
//中序遍历：左-根-右
void Linktree_Mid(Tree_node *root)
{
    if(root == NULL)
    {
        return ;
    }
    Linktree_Mid(root->l_child);
    printf("%c", root->data);
    Linktree_Mid(root->r_child);   
}

//后序遍历：左-右-根
void Linktree_After(Tree_node *root)
{
    if(root == NULL)
    {
        return ;
    }
    Linktree_After(root->l_child);
    Linktree_After(root->r_child);
    printf("%c", root->data);
}

//层次遍历
void Linktree_Level(Tree_node *root)
{
    //创建一个队列
    Sequeue *queue = Sequeue_Create();
    //根节点的地址入队
    Sequeue_In(queue, root);
    //当队列不空，执行内部语句
    while(queue->front != queue->rear)
    {
        //如果当前队列首元素指向的节点有左孩子，则把左孩子入队
        if(queue->data[queue->front]->l_child != NULL)Sequeue_In(queue, queue->data[queue->front]->l_child);
        //如果当前队列首元素指向的节点有右孩子，则把右孩子入队
        if(queue->data[queue->front]->r_child != NULL)Sequeue_In(queue, queue->data[queue->front]->r_child);
        //队列首元素指向的节点的值出队
        printf("%c", Sequeue_Out(queue)->data);
    }
    //销毁队列
    Sequeue_Destory(&queue);
}



//创建队列
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
//入队
void Sequeue_In(Sequeue *queue, Tree_node * data)
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
Tree_node *Sequeue_Out(Sequeue *queue)
{
    if(queue->rear == queue->front)
    {
        printf("queue is empty!\n");
        return NULL;
    }

    Tree_node *out = queue->data[queue->front];
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