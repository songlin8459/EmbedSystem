#include <stdio.h>
typedef int data_t;
//选择排序
void Sort_Select(data_t *arr, int len)
{
    int i, j;
    for(i = 0; i < len - 1; i++)
    {
        for(j = i + 1; j < len; j++)
        {
            if(arr[i] > arr[j])
            {
                int tmp;
                tmp = arr[i];
                arr[i]  = arr[j];
                arr[j] = tmp;
            }
        }
    }
}
//冒泡排序
void Sort_Bubb(data_t *arr, int len)
{
    int i, j;
    for(i = 0; i < len - 1; i++)
    {
        for(j = 0; j < len - 1 - i; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                int tmp;
                tmp = arr[j];
                arr[j]  = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}
//插入排序
void Sort_Insert(data_t *arr, int len)
{
    int i, j;
    data_t tmp;

    for(i = 1; i < len; i++)
    {
        tmp = arr[i];
        for(j = i-1; j >= 0; j--)
        {
            if(tmp < arr[j])
            {
                arr[j+1] = arr[j];
            }
            else
            {
                break;
            }
        }
        arr[j+1] = tmp;
    }
}
//快速排序
void Sort_Fast(data_t *arr, int low, int high)
{
    int i = low, j = high;
    data_t tmp = arr[i];
    if(i >= j)
    {
        return ;
    }
    while(i < j)
    {
        while((i < j) && (tmp <= arr[j]))
        {
            j--;
        }
        arr[i] = arr[j]; 
        while((i < j) && (arr[i] <= tmp))
        {
            i++;
        }
        arr[j] = arr[i];
    }
    arr[i] = tmp;
    Sort_Fast(arr, low, j - 1);
    Sort_Fast(arr, i + 1, high);
}
int main()
{
    int arr[10] = {5, 8, 9, 7, 6, 3, 4, 1, 2};
    //计算数组长度
    int len = 0;
    while(arr[len])len++;  
    printf("len = %d\n", len);
    //调用函数
    Sort_Insert(arr, len);
    //打印数组
    int i;
    for(i = 0; i < len; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }


    int arr2[10] = {5, 8, 9, 7, 6, 3, 4, 1, 2};
    //计算数组长度
    int len2 = 0;
    while(arr[len2] != '\0')len2++;  
    printf("len2 = %d\n", len2);
    //调用函数
    Sort_Fast(arr2, 0, 8);
    //打印数组

    for(i = 0; i < 9; i++)
    {
        printf("arr2[%d] = %d\n", i, arr2[i]);
    }
    return 0;
}