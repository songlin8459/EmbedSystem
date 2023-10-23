#include "linklist_loop.h"
#define NUM 64
int main()
{
    /*======================测试约瑟夫函数================================*/
 
    int num, start, count;
    //链表长度
    printf("linklist length(<=%d):",NUM);
    scanf("%d", &num);

    //计数开始位置
    printf("count start:");
    scanf("%d", &start);

    //步长
    printf("count length:");
    scanf("%d", &count);

    data_t arr[NUM] = {0};
    //执行约瑟夫函数
    Linklist_Loop_Joseph(num , start, count, arr);
    //输出数组
    printf("output arr:");
    for(int i  = 0; i < num; i++)
    {
        printf("%d ",arr[i]);
    }

   /*======================测试链表合并函数================================*/
//    //创建第一条链表
//     Node *first = Linklist_Loop_Create();
//     //定义第一条链表长度
//     int len_first;
//     printf("first linklsit length :");
//     scanf("%d", &len_first);
//     //插入第一条链表剩下节点
//     int i;
//     for(i = len_first - 1; i >= 0; i--)
//     {
//         Linklist_Loop_Insert_Head(first,i);
//     }
//     Linklist_Loop_Show(first);
//     printf("\n");
//    //创建第二条链表
//     Node *second = Linklist_Loop_Create();
//     //定义第二条链表长度
//     int len_second;
//     printf("second linklsit length :");
//     scanf("%d", &len_second);
//     //插入第二条链表剩下节点
//     for(i = len_second - 1; i >= 0; i--)
//     {
//         Linklist_Loop_Insert_Head(second,i);
//     }
//     Linklist_Loop_Show(second);
//     printf("\n");
//     //调用合并函数
//     Node *incor = Linklist_Loop_Incor(first,second);
//     Linklist_Loop_Show(incor);
//     //销毁链表
//     Linklist_Loop_Destory(&first);
//     Linklist_Loop_Destory(&second);
//     Linklist_Loop_Destory(&incor);
    return 0;
}