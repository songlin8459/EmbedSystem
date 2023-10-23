#include "seqlist.h"

int main()
{
    Seqlist *list = Seqlist_Create();
    for(int i = 0; i < 10; i++)
    {
        Seqlist_Insert_Pos(list, i ,i);
    }
    Seqlist_Show(list);

    data_t data = Seqlist_Search_Pos(list, 5);
    printf("%d\n", data);

    Seqlist_Updata_Data(list, 5, 0);
    Seqlist_Show(list);

    int address = Seqlist_Search_Data(list, 9);
    printf("%d\n", address);

    Seqlist_Destory(&list);
    Seqlist_Show(list);
    return 0;
}

