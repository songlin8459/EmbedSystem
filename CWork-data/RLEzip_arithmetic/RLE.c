#include "RLE.h"
/*===========================================压缩zip=================================================*/
CONT *ZIP(char *arr)
{
    /*定义一个结构体来存放RLE压缩后的数据*/
    CONT *cont_final;
    /*i:遍历 k：赋值 len：原数组长度 counter：统计相同单位数量*/
    int i, k = 0, len = 0, counter = 1;
    /*计算原数组长度*/
    while(arr[len])len++;
    /*遍历原数组*/
    for(i = 0; i < len; i = i + counter)
    {
        counter = 1;
        /*从该位置开始，依次和后续位置的单位数据比较*/
        for(int j = i + 1; j < len; j++)
        {
            /*如果不相等，退出循环*/
            if(arr[i] != arr[j]) break;
            /*如果相等，计数位加1*/
            else counter++;
        } 
        cont_final->cont[k] = arr[i];
        cont_final->cont_n[k] = counter;
        k++; 
    }
    cont_final->counter_final = k;
    return cont_final;
}

/*===========================================解压unzip=================================================*/
CONT *UNZIP(CONT *incont)
{
    CONT *result;
    char arr[N] = {0};
    int i = 0, j = 0, start = 0;
    /*遍历cont_n*/
    for(i = 0; i < incont->counter_final; i++)
    {
        while(incont->cont_n[i])
        {
            arr[j] = incont->cont[i];
            result->cont[j] = arr[j];
            j++;
            incont->cont_n[i]--;       
        }
    }
    result->counter_final = j;    
    return result;
}