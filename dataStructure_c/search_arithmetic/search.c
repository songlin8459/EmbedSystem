#include "search.h"
/*============================================================================================*/
/*创建顺序表*/
Seqlist *Seqlist_Create(void)
{
    /*在堆区给结构体开辟空间供结构体使用*/
    Seqlist *list = (Seqlist *)malloc(sizeof(Seqlist)); 
    /*如果堆空间开辟失败*/
    if(list == NULL)   
    {
        printf("malloc failed!\n");
        return NULL;
    }
    list->last = -1;
    return list;
}
/*============================================================================================*/
/*插入元素*/
void Seqlist_Insert_Pos(Seqlist *list, int pos, data_t data)
{
    /*判断插入位置是否有效*/
    if(pos < 0 || pos > list->last + 1)
    {
            printf("pos error!\n");
            return;
    }
    /*判断顺序表是否为满*/
    if(Seqlist_Is_Full(list) == 1)
    {
        printf("seqlist is full!\n");
        return;
    }
    /*元素移动*/
    int i; 
    for(i = list->last; i >= pos; i-- )
    {
        list->data[i + 1] = list->data[i];
    }
    /*元素插入*/
    list->data[pos] = data;
    /*下标改变*/
    list->last++;
}
/*============================================================================================*/
/*判满*/
int Seqlist_Is_Full(Seqlist *list)
{
    if(list->last == N - 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
/*============================================================================================*/
/*判空*/
int Seqlist_Is_Empty(Seqlist *list)
{
    if(list->last == -1)return 1;
    else return 0;
}
/*============================================================================================*/
/*打印表*/
void Seqlist_Show(Seqlist *list)
{
	int i;
    for(i = 0; i <= list->last; i++)
    {
        printf("%d ",list->data[i]);
    }
    puts("");
}
/*============================================================================================*/
/*删除指定位置元素*/
void Seqlist_Delete_Pos(Seqlist *list, int pos)
{
    /*判空*/
    if(Seqlist_Is_Empty(list) == 1)
    {
        printf("seqlist is empty!\n");
        return;
    }
    /*移位*/
	int i;
    for( i = pos; i < list->last; i++)
    {
        list->data[i] = list->data[i+1];
    }
    list->last--;
}
/*============================================================================================*/
/*删除指定数据元素*/
void Seqlist_Delete_Data(Seqlist *list, data_t data)
{
    /*判空*/
    if(Seqlist_Is_Empty(list) == 1)
    {
        printf("seqlist is empty!\n");
        return;
    }
    /*定义标志位flag作为是否删除标志*/
    int flag = list->last;
    int i;
    /*遍历表*/
    for(i = 0; i <= list->last; i++)
    {
        /*如果有这样一个元素，执行移位*/
        if(data == list->data[i])
        {
            /*执行移位*/
            for(int j = i; j < list->last; j++)
            {
                list->data[j] = list->data[j + 1];
            }
            /*下标减1*/
            list->last--;
            i--;
        }  
    }
    /*如果flag=last,证明无删除操作，结束函数*/
    if(flag == list->last)
    {
        printf("no such data!\n");
    }
    else
    {
        printf("delete success!\n");
    }
    return;
}
/*============================================================================================*/
/*修改指定位置元素*/
void Seqlist_Updata_Pos(Seqlist *list, int pos, data_t data)
{
    /*判空*/
    if(Seqlist_Is_Empty(list) == 1)
    {
        printf("seqlist is empty!\n");
        return;
    }
    /*修改元素*/
    list->data[pos] = data;
}
/*============================================================================================*/
/*修改指定数据元素*/
void Seqlist_Updata_Data(Seqlist *list, data_t data_original, data_t data_new)
{
    /*判空*/
    if(Seqlist_Is_Empty(list) == 1)
    {
        printf("seqlist is empty!\n");
        return;
    }
    /*定义标志位flag作为是否修改标志*/
    int flag = 0;
    int i;
    /*遍历表*/
    for(i = 0; i <= list->last; i++)
    {
        /*如果有这样一个元素，修改元素*/
        if(data_original == list->data[i])
        {
            /*执行修改*/
            list->data[i] = data_new;
            /*标志位flag变1，表明成功修改*/
            flag = 1;
        }  
    }
    /*如果flag=0,证明无修改操作，结束函数*/
    if(flag == 0)
    {
        printf("no such data!\n");
    }
    else
    {
        printf("updata success!\n");
    }
    return;     
}
/*============================================================================================*/
/*查找指定位置元素*/
data_t Seqlist_Search_Pos(Seqlist *list, int pos)
{
     /*判空*/
    if(Seqlist_Is_Empty(list) == 1)
    {
        printf("seqlist is empty!\n");
        return 0;
    }
     /*判断位置错误*/
    if(pos < 0 || pos > list->last)
    {
        printf("pos error!\n");
    }
    /*返回查找的元素*/
    return list->data[pos];
}
/*============================================================================================*/
/*查找指定数据元素*/
int Seqlist_Search_Data(Seqlist *list, data_t data)
{
    /*判空*/
    if(Seqlist_Is_Empty(list) == 1)
    {
        printf("seqlist is empty!\n");
        return 0;
    }
    /*定义标志位flag作为是否找到*/
    int flag = 0, address;
    int i;
    /*遍历表*/
    for(i = 0; i <= list->last; i++)
    {
        /*如果有这样一个元素，其下标赋给address,给flag赋1*/
        if(data == list->data[i])
        {
            flag = 1;
            address = i;
            break;
        }          
    }
    if(flag == 0)
    {
        return 0;
    }
    else
    {
        return address;
    }
}
/*============================================================================================*/
/*删除表*/
void Seqlist_Destory(Seqlist **plist)
{
    
    free(*plist);
    *plist = NULL;
}

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

/*============================================================================================*/
/*折半查找*/

int Search_Mid(Seqlist *list, data_t key)
{
    /*判空*/
    if(Seqlist_Is_Empty(list) == 1)
    {
        printf("seqlist is empty!\n");
        return 0;
    }
    int low = 0;
    int high = list->last;
    while(low <= high)
    {
        int mid = (low + high)/2;
        if(list->data[mid] > key) high = mid - 1;
        else if(list->data[mid] < key) low = mid + 1;
        else return mid;

    }
    return -1;
}

/*============================================================================================*/
/*Hash查找*/

int Search_Hash(Seqlist *list, int len_old, int len_hash, int prime_number, data_t key)
{
    //判空
    if(Seqlist_Is_Empty(list) == 1)
    {
        printf("seqlist is empty!\n");
        return -1;
    }
    //创建长度为len_hash的结构体指针数组
    const int len = len_hash;
    Node *hash[len];
    //为结构体指针数组开辟空间
    Node **p = (Node **)malloc(sizeof(Node *) * len);
    //查看结构体指针的内容（存放的地址）
    int i;
    for(i = 0; i < len; i++)
    {
        hash[i] = p[i];
        printf("hash[%d] = %p\n", i, &hash[i]);
    }
    //释放结构体指针数组
    Node ***q = &p;
    free(*q);

 /*  
    //初始化结构体数组
    int i;
    for(i = 0; i < len_hash; i++)
    {
        hash[i].data = -1;
        hash[i].next = NULL;
    }

    //定义变量
    int pos;
    Node *p = NULL, *q = NULL;

    //创建hash表
    for(i = 0; i < len_old; i++)
    {
        //遍历原表中元素，计算其在hash表中位置
        pos = list->data[i]%prime_number;
        p = &hash[pos];
        //如果当前位置data为-1
        if(p->data == -1)
        {
            p->data = list->data[pos];
        }
        else
        {
            //头部插入
            Linklist_Insert_Head(p, list->data[i]);
        }
    }
    
    //hash查找
    //计算key在hash表中位置
    pos = key%prime_number;
    if(hash[pos].data == -1)
    {
        return -1;
    }
    else if(hash[pos].data == key)
    {
        return pos;
    }
    else
    {
        p = hash[pos].next;
        while(p != NULL)
        {
            if(p->data == key) return pos;
            else p = p->next;
        }
    }
*/
}