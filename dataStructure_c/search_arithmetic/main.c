#include "search.h"

int main()
{
    //创建顺序表
    Seqlist *list = Seqlist_Create();
    for(int i = 0; i < 20; i++)
    {
        Seqlist_Insert_Pos(list, i , i*i);
    }
    Seqlist_Show(list);
/*折半查找*/
    data_t key;
    printf("key is:");
    scanf("%d", &key);
    int pos = Search_Mid(list, key);
    printf("mid | key located at:%d\n",pos);
    printf("..........................\n");
/*hash查找*/
    //计算原表长
    int old = list->last + 1;
    //设装填因子为0.75
    int load = 0.75;
    //计算hash表长
    int len_hash = ceil(old/0.75);
    //printf("len_hash:%d\n", len_hash);
    // 输入质数
    //printf("prime_number:");  
    int prime_number;
    //scanf("%d", &prime_number);
    //调用hash查找函数
    int loc = Search_Hash(list, old, len_hash, 23, key);
    printf("hash | key located at:%d",loc);   
    return 0;
}