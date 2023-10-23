#include "RLE.h"

int main()
{
    /*测试UNZIP函数*/  
    char a[N] = "HJJJJJJJJJJIIIIIIIIIIIIIIINNNNNNNMMMMMMMEE";
    CONT *cont_final = ZIP(a);
    int len_c = cont_final->counter_final;
    int l;
    printf("after ZIP:\n");
    for(l = 0; l < len_c; l++)
    {
        printf("%c ",cont_final->cont[l]);
        printf("%d ",cont_final->cont_n[l]);
    }

    printf("\n===ZIP test success!===\n");
    
    /*测试UNZIP函数*/  
    CONT *test = UNZIP(cont_final);
    printf("after UNZIP:\n");
    int k;
    for(k = 0; k < test->counter_final; k++)
    {
        printf("%c ", test->cont[k]);
    }
    printf("\n==UNZIP test success!==\n");
    return 0;
}